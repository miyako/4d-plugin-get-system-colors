![version](https://img.shields.io/badge/version-17%2B-3E8B93)
![platform](https://img.shields.io/static/v1?label=platform&message=mac-intel%20|%20mac-arm&color=blue)
[![license](https://img.shields.io/github/license/miyako/4d-plugin-get-system-colors)](LICENSE)
![downloads](https://img.shields.io/github/downloads/miyako/4d-plugin-get-system-colors/total)

**Note**: for v17 and earlier, move `manifest.json` to `Contents`

# 4d-plugin-get-system-colors
for macOS (10.13 SDK, before dark mode)

### Examples

```
If (Form event=On Load)
	$c:=JSON Parse(Get system colors )
	
	OBJECT GET COORDINATES(*;"T0";$x;$y;$r;$b)
	$h:=$b-$y
	$w:=$r-$x
	
	C_POINTER($NIL)
	$x:=0
	$y:=0
	
	For each ($color;$c)
		
		OBJECT DUPLICATE(*;"T0";$color;$NIL;"";$x;$y;*)
		$y:=$y+$h
		
		OBJECT SET RGB COLORS(*;$color;Choose($c[$color]=0x0000;0xFFFF;0x0000);$c[$color])
		
		$hex:=String($c[$color];"&x")
		$hex:="000000"+Substring($hex;3)
		$hex:=Substring($hex;Length($hex)-5)
		
		OBJECT SET TITLE(*;$color;$color+" #"+$hex)
		
	End for each 
End if 
```
