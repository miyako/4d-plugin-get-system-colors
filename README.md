# 4d-plugin-get-system-colors
for macOS (10.13 SDK, before dark mode)

<img width="486" alt="2018-11-01 17 32 02" src="https://user-images.githubusercontent.com/1725068/47841209-337b0f00-ddfc-11e8-91b7-913994c9a33b.png">

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
