#include "FrameBufferInfoAPI.h"
#include "FrameBufferInfo.h"
#include "OpenGL.h"
#include "FrameBuffer.h"
#include "DepthBuffer.h"
#include "VI.h"
#include "Log.h"

void FrameBufferWrite(u32 addr, u32 size)
{
	debugPrint("FBWrite addr=%08lx size=%u\n", addr, size);
}

void FrameBufferWriteList(FrameBufferModifyEntry *plist, u32 size)
{
	debugPrint("FBWList size=%u\n", size);
	for (u32 i = 0; i < size; ++i)
		debugPrint(" plist[%u] addr=%08lx val=%08lx size=%u\n", i, plist[i].addr, plist[i].val, plist[i].size);
}

void FrameBufferRead(u32 addr)
{
	debugPrint("FBRead addr=%08lx \n", addr);
}

void FrameBufferGetInfo(void *pinfo)
{
	FrameBufferInfo * pFBInfo = (FrameBufferInfo*)pinfo;
	memset(pFBInfo, 0, sizeof(FrameBufferInfo)* 6);
	u32 idx = 0;
	DepthBuffer * pDepthBuffer = depthBufferList().getCurrent();
	if (pDepthBuffer != nullptr) {
		pFBInfo[idx].addr = pDepthBuffer->m_address;
		pFBInfo[idx].width = pDepthBuffer->m_width;
		pFBInfo[idx].height = VI.real_height;
		pFBInfo[idx++].size = 2;
	}
	frameBufferList().fillBufferInfo(&pFBInfo[idx], 6 - idx);
}
