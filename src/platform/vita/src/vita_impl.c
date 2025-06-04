#include <vitasdk.h>
#include <stdio.h>
#include <SDL.h>
#include <sys/stat.h>
#include <stdbool.h>
#include "../../../types.h"
#include "../../../util.h"

int __real_mkdir(const char *fname, mode_t mode);
FILE * __real_fopen(char *fname, char *mode);

int _newlib_heap_size_user = 128 * 1024 * 1024;

void VitaImpl_Init() {
    scePowerSetArmClockFrequency(444);
    scePowerSetBusClockFrequency(222);
    scePowerSetGpuClockFrequency(222);
    scePowerSetGpuXbarClockFrequency(166);
    //To create base directory if necessary
    mkdir("", 0777);
}

void OpenGLRenderer_Create(struct RendererFuncs *funcs) {

}

// State Vita SDL Renderer
static SDL_Renderer *vita_renderer;
static SDL_Texture *vita_texture;
static SDL_Rect window_rect, rendering_rect, texture_rect;

static bool VitaRenderer_Init(SDL_Window *window) {
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL) {
        printf("Failed to create renderer: %s\n", SDL_GetError());
        return false;
    }

    vita_renderer = renderer;

    vita_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, 256, 240);
    if (vita_texture == NULL) {
        printf("Failed to create texture: %s\n", SDL_GetError());
        return false;
    }

    window_rect.x = 169;
    window_rect.y = 0;
    window_rect.w = 622;
    window_rect.h = 544;

    rendering_rect.x = 0;
    rendering_rect.y = 0;
    rendering_rect.w = 256;
    rendering_rect.h = 240;

    texture_rect.x = 0;
    texture_rect.y = 0;
    texture_rect.w = 256;
    texture_rect.h = 224;
    return true;
}

static void VitaRenderer_Destroy(void) {
    SDL_DestroyTexture(vita_texture);
    SDL_DestroyRenderer(vita_renderer);
}

static void VitaRenderer_BeforeFrame(void **memoryBuffer) {
    int pitch;
    if (SDL_LockTexture(vita_texture, &rendering_rect, memoryBuffer, &pitch) != 0) {
        printf("Failed to lock texture: %s\n", SDL_GetError());
        //TODO fail program
    }
}

static void VitaRenderer_BeginDraw(int width, int height, uint8 **pixels, int *pitch) {
    *pixels = NULL;
}

static void VitaRenderer_EndDraw(void) {
    SDL_UnlockTexture(vita_texture);
    SDL_RenderClear(vita_renderer);
    SDL_RenderCopy(vita_renderer, vita_texture, &texture_rect, &window_rect);
    SDL_RenderPresent(vita_renderer);
}

static const struct RendererFuncs kVitaRendererFuncs = {
        &VitaRenderer_Init,
        &VitaRenderer_Destroy,
        &VitaRenderer_BeforeFrame,
        &VitaRenderer_BeginDraw,
        &VitaRenderer_EndDraw,
};

void VitaRenderer_Create(struct RendererFuncs *funcs) {
    *funcs = kVitaRendererFuncs;
}

int __wrap_mkdir(const char *fname, mode_t mode) {
    char patched_fname[256];
    sprintf(patched_fname, "ux0:data/smetroid/%s", fname);
    return __real_mkdir(patched_fname, mode);
}

FILE *__wrap_fopen(char *fname, char *mode) {
    //Use the vpk-provided ini
    if(strcmp(fname, "sm.ini") == 0) {
      return __real_fopen(fname, mode);
    }
    char patched_fname[256];
    sprintf(patched_fname, "ux0:data/smetroid/%s", fname);
    return __real_fopen(patched_fname, mode);
}
