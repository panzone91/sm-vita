#pragma once

void VitaImpl_Init();
void VitaRenderer_Create(struct RendererFuncs *funcs);
bool VitaRenderer_BeforeFrame(void **memoryBuffer);
