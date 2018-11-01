/* --------------------------------------------------------------------------------
 #
 #	4DPlugin.cpp
 #	source generated by 4D Plugin Wizard
 #	Project : System Colors
 #	author : miyako
 #	2018/11/01
 #
 # --------------------------------------------------------------------------------*/


#include "4DPluginAPI.h"
#include "4DPlugin.h"

std::mutex mutexJson;

void PluginMain(PA_long32 selector, PA_PluginParameters params)
{
	try
	{
		PA_long32 pProcNum = selector;
		sLONG_PTR *pResult = (sLONG_PTR *)params->fResult;
		PackagePtr pParams = (PackagePtr)params->fParameters;

		CommandDispatcher(pProcNum, pResult, pParams); 
	}
	catch(...)
	{

	}
}

void CommandDispatcher (PA_long32 pProcNum, sLONG_PTR *pResult, PackagePtr pParams)
{
	switch(pProcNum)
	{
// --- Get System Color

		case 1 :
			Get_system_colors(pResult, pParams);
			break;

	}
}

// ------------------------------- Get System Color -------------------------------

unsigned int getColorRGB(NSColor *color)
{
    unsigned int rgb = 0;
    
    if(color)
    {
        color = [color colorUsingColorSpace:[NSColorSpace displayP3ColorSpace]];
        
        /*
         color = [color colorUsingColorSpace:[NSColorSpace deviceRGBColorSpace]];//NSDeviceRGBColorSpace
         color = [color colorUsingColorSpace:[NSColorSpace sRGBColorSpace]];
         color = [color colorUsingColorSpace:[NSColorSpace genericRGBColorSpace]];//NSCalibratedRGBColorSpace
         */
        
        CGFloat red, green, blue, alpha;
        [color getRed:&red green:&green blue:&blue alpha:&alpha];
        
        rgb +=
        
        /*
         +((unsigned int)(red      * 255.99999f) << 16)
         +((unsigned int)(green    * 255.99999f) << 8)
         + (unsigned int)(blue     * 255.99999f);
         */
        
        +((unsigned int)floor((CGFloat)(red      * 0xFF) + 0.5f) << 16)
        +((unsigned int)floor((CGFloat)(green    * 0xFF) + 0.5f) << 8)
        + (unsigned int)floor((CGFloat)(blue     * 0xFF) + 0.5f);
    }
    
    return rgb;
}

void Get_system_colors(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT returnValue;

    CUTF16String json;
    
    if(1)
    {
        std::lock_guard<std::mutex> lock(mutexJson);
        
        JSONNODE *info = json_new(JSON_NODE);

        json_set_i_for_key(info, L"controlShadowColor", getColorRGB([NSColor controlShadowColor]));
        json_set_i_for_key(info, L"controlDarkShadowColor", getColorRGB([NSColor controlDarkShadowColor]));
        json_set_i_for_key(info, L"controlColor", getColorRGB([NSColor controlColor]));
        json_set_i_for_key(info, L"controlHighlightColor", getColorRGB([NSColor controlHighlightColor]));
        json_set_i_for_key(info, L"controlLightHighlightColor", getColorRGB([NSColor controlLightHighlightColor]));
        json_set_i_for_key(info, L"controlTextColor", getColorRGB([NSColor controlTextColor]));
        json_set_i_for_key(info, L"controlBackgroundColor", getColorRGB([NSColor controlBackgroundColor]));
        json_set_i_for_key(info, L"selectedControlColor", getColorRGB([NSColor selectedControlColor]));
        json_set_i_for_key(info, L"secondarySelectedControlColor", getColorRGB([NSColor secondarySelectedControlColor]));
        
        json_set_i_for_key(info, L"selectedControlTextColor", getColorRGB([NSColor selectedControlTextColor]));
        json_set_i_for_key(info, L"disabledControlTextColor", getColorRGB([NSColor disabledControlTextColor]));
        json_set_i_for_key(info, L"textColor", getColorRGB([NSColor textColor]));
        json_set_i_for_key(info, L"textBackgroundColor", getColorRGB([NSColor textBackgroundColor]));
        json_set_i_for_key(info, L"selectedTextColor", getColorRGB([NSColor selectedTextColor]));
        json_set_i_for_key(info, L"selectedTextBackgroundColor", getColorRGB([NSColor selectedTextBackgroundColor]));
        json_set_i_for_key(info, L"gridColor", getColorRGB([NSColor gridColor]));
        json_set_i_for_key(info, L"keyboardFocusIndicatorColor", getColorRGB([NSColor keyboardFocusIndicatorColor]));
        json_set_i_for_key(info, L"windowBackgroundColor", getColorRGB([NSColor windowBackgroundColor]));
        json_set_i_for_key(info, L"underPageBackgroundColor", getColorRGB([NSColor underPageBackgroundColor]));
        
        json_set_i_for_key(info, L"labelColor", getColorRGB([NSColor labelColor]));
        json_set_i_for_key(info, L"secondaryLabelColor", getColorRGB([NSColor secondaryLabelColor]));
        json_set_i_for_key(info, L"tertiaryLabelColor", getColorRGB([NSColor tertiaryLabelColor]));
        json_set_i_for_key(info, L"quaternaryLabelColor", getColorRGB([NSColor quaternaryLabelColor]));
        
        json_set_i_for_key(info, L"scrollBarColor", getColorRGB([NSColor scrollBarColor]));
        json_set_i_for_key(info, L"knobColor", getColorRGB([NSColor knobColor]));
        json_set_i_for_key(info, L"selectedKnobColor", getColorRGB([NSColor selectedKnobColor]));
        
        json_set_i_for_key(info, L"windowFrameColor", getColorRGB([NSColor windowFrameColor]));
        json_set_i_for_key(info, L"windowFrameTextColor", getColorRGB([NSColor windowFrameTextColor]));
        
        json_set_i_for_key(info, L"selectedMenuItemColor", getColorRGB([NSColor selectedMenuItemColor]));
        json_set_i_for_key(info, L"selectedMenuItemTextColor", getColorRGB([NSColor selectedMenuItemTextColor]));
        
        json_set_i_for_key(info, L"highlightColor", getColorRGB([NSColor highlightColor]));
        
        json_set_i_for_key(info, L"shadowColor", getColorRGB([NSColor shadowColor]));
        
        json_set_i_for_key(info, L"headerColor", getColorRGB([NSColor headerColor]));
        json_set_i_for_key(info, L"headerTextColor", getColorRGB([NSColor headerTextColor]));
        
        json_set_i_for_key(info, L"alternateSelectedControlColor", getColorRGB([NSColor alternateSelectedControlColor]));
        json_set_i_for_key(info, L"alternateSelectedControlTextColor", getColorRGB([NSColor alternateSelectedControlTextColor]));

        json_set_i_for_key(info, L"scrubberTexturedBackgroundColor", getColorRGB([NSColor scrubberTexturedBackgroundColor]));

        
        json_stringify(info, json, FALSE);
        json_delete(info);
    }
    
    returnValue.setUTF16String(&json);
	returnValue.setReturn(pResult);
}

