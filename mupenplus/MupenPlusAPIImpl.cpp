#include "GLideN64_mupenplus.h"
#include "../PluginAPI.h"
#include "../GLideN64.h"
#include "../OpenGL.h"

#ifdef _WINDOWS
#define DLSYM(a, b) GetProcAddress(a, b)
#else
#define DLSYM(a, b) dlsym(a, b)
#endif // _WINDOWS

ptr_ConfigGetSharedDataFilepath ConfigGetSharedDataFilepath = NULL;
ptr_ConfigGetUserConfigPath ConfigGetUserConfigPath = NULL;

/* definitions of pointers to Core video extension functions */
ptr_VidExt_Init                  CoreVideo_Init = NULL;
ptr_VidExt_Quit                  CoreVideo_Quit = NULL;
ptr_VidExt_ListFullscreenModes   CoreVideo_ListFullscreenModes = NULL;
ptr_VidExt_SetVideoMode          CoreVideo_SetVideoMode = NULL;
ptr_VidExt_SetCaption            CoreVideo_SetCaption = NULL;
ptr_VidExt_ToggleFullScreen      CoreVideo_ToggleFullScreen = NULL;
ptr_VidExt_ResizeWindow          CoreVideo_ResizeWindow = NULL;
ptr_VidExt_GL_GetProcAddress     CoreVideo_GL_GetProcAddress = NULL;
ptr_VidExt_GL_SetAttribute       CoreVideo_GL_SetAttribute = NULL;
ptr_VidExt_GL_GetAttribute       CoreVideo_GL_GetAttribute = NULL;
ptr_VidExt_GL_SwapBuffers        CoreVideo_GL_SwapBuffers = NULL;

void (*renderCallback)() = NULL;

m64p_error PluginAPI::PluginStartup(m64p_dynlib_handle _CoreLibHandle)
{
	ConfigGetSharedDataFilepath = (ptr_ConfigGetSharedDataFilepath)	DLSYM(_CoreLibHandle, "ConfigGetSharedDataFilepath");
	ConfigGetUserConfigPath = (ptr_ConfigGetUserConfigPath)	DLSYM(_CoreLibHandle, "ConfigGetUserConfigPath");

	/* Get the core Video Extension function pointers from the library handle */
	CoreVideo_Init = (ptr_VidExt_Init) DLSYM(_CoreLibHandle, "VidExt_Init");
	CoreVideo_Quit = (ptr_VidExt_Quit) DLSYM(_CoreLibHandle, "VidExt_Quit");
	CoreVideo_ListFullscreenModes = (ptr_VidExt_ListFullscreenModes) DLSYM(_CoreLibHandle, "VidExt_ListFullscreenModes");
	CoreVideo_SetVideoMode = (ptr_VidExt_SetVideoMode) DLSYM(_CoreLibHandle, "VidExt_SetVideoMode");
	CoreVideo_SetCaption = (ptr_VidExt_SetCaption) DLSYM(_CoreLibHandle, "VidExt_SetCaption");
	CoreVideo_ToggleFullScreen = (ptr_VidExt_ToggleFullScreen) DLSYM(_CoreLibHandle, "VidExt_ToggleFullScreen");
	CoreVideo_ResizeWindow = (ptr_VidExt_ResizeWindow) DLSYM(_CoreLibHandle, "VidExt_ResizeWindow");
	CoreVideo_GL_GetProcAddress = (ptr_VidExt_GL_GetProcAddress) DLSYM(_CoreLibHandle, "VidExt_GL_GetProcAddress");
	CoreVideo_GL_SetAttribute = (ptr_VidExt_GL_SetAttribute) DLSYM(_CoreLibHandle, "VidExt_GL_SetAttribute");
	CoreVideo_GL_GetAttribute = (ptr_VidExt_GL_GetAttribute) DLSYM(_CoreLibHandle, "VidExt_GL_GetAttribute");
	CoreVideo_GL_SwapBuffers = (ptr_VidExt_GL_SwapBuffers) DLSYM(_CoreLibHandle, "VidExt_GL_SwapBuffers");

	return M64ERR_SUCCESS;
}

m64p_error PluginAPI::PluginShutdown()
{
#ifdef RSPTHREAD
	_callAPICommand(acRomClosed);
	delete m_pRspThread;
	m_pRspThread = NULL;
#else
	video().stop();
#endif
	return M64ERR_SUCCESS;
}

m64p_error PluginAPI::PluginGetVersion(
	m64p_plugin_type * _PluginType,
	int * _PluginVersion,
	int * _APIVersion,
	const char ** _PluginNamePtr,
	int * _Capabilities
)
{
	/* set version info */
	if (_PluginType != NULL)
		*_PluginType = M64PLUGIN_GFX;

	if (_PluginVersion != NULL)
		*_PluginVersion = PLUGIN_VERSION;

	if (_APIVersion != NULL)
		*_APIVersion = VIDEO_PLUGIN_API_VERSION;

	if (_PluginNamePtr != NULL)
		*_PluginNamePtr = pluginName;

	if (_Capabilities != NULL)
	{
		*_Capabilities = 0;
	}

	return M64ERR_SUCCESS;
}

void PluginAPI::SetRenderingCallback(void (*callback)(int))
{
	static void (*renderCallback)(int) = NULL;
	renderCallback = callback;
}

void PluginAPI::StartGL()
{
}

void PluginAPI::StopGL()
{
}

void PluginAPI::ResizeGL(int _width, int _height)
{
}