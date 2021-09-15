// Basic XPL skeleton

#include <XPLMMenus.h>
#include <XPLMPlugin.h>
#include <string>

#if IBM
	#include <Windows.h>
#endif // IBM

int menuIdx;
XPLMMenuID menu;

void startMenu(void);
void finishMenu(void);
void menuHandler(void*, void*);

/**********************************************
	REQUIRED CALLBACKS
**********************************************/

// Called by XPlane when DLL is loaded - Returns 1 when successfully loaded
PLUGIN_API int XPluginStart(char *name, char *signature, char *description) {
	char n[] = "xPlugin Reloader";
	char s[] = "net.jazbelt.xpluginreloader";
	char d[] = "Reload all plugins from XPlane in-game menu";
	strcpy_s(name, sizeof(n), n);
	strcpy_s(signature, sizeof(s), s);
	strcpy_s(description, sizeof(d), d);

	startMenu();

	return 1;
}

// Called before the DLL is unloaded
PLUGIN_API void XPluginStop(void) {
	finishMenu();
}

// Called before the plugin is enabled - Returns 1 when successfully starts
PLUGIN_API int XPluginEnable(void) {
	return 1;
}

// Called before the plugin is disabled
PLUGIN_API void XPluginDisable(void) {}

//Called by Plugin Manager when message is sent to us
PLUGIN_API void XPluginReceiveMessage(XPLMPluginID from, int message, void *param) {}

// Initialize menu
void startMenu(void) {
	XPLMMenuID pluginsMenu = XPLMFindPluginsMenu();
	menuIdx = XPLMAppendMenuItem(pluginsMenu, "xPlugin Reloader", (void*)"PLUGINS_RELOAD_MENU", 0);
	menu = XPLMCreateMenu("xPlugin Reloader", pluginsMenu, menuIdx, menuHandler, NULL);
	XPLMAppendMenuItem(menu, "Reload all plugins", (void*)"RELOAD_PLUGINS", 0);
}

// Destroy menu
void finishMenu(void) {
	if (menu != NULL) {
		XPLMDestroyMenu(menu);
		menu = NULL;
	}
}

// Handle menu actions
void menuHandler(void* menuRef, void* itemRef) {
	const char* action = (const char*)itemRef;

	if(!strcmp(action, "RELOAD_PLUGINS")) {
		XPLMReloadPlugins();
	}
}
