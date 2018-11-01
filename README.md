# 4d-plugin-get-system-colors
for macOS (10.13 SDK, before dark mode)

### Platform

| carbon | cocoa | win32 | win64 |
|:------:|:-----:|:---------:|:---------:|
|<img src="https://cloud.githubusercontent.com/assets/1725068/22371562/1b091f0a-e4db-11e6-8458-8653954a7cce.png" width="24" height="24" />|<img src="https://cloud.githubusercontent.com/assets/1725068/22371562/1b091f0a-e4db-11e6-8458-8653954a7cce.png" width="24" height="24" />|||

### Version

<img src="https://cloud.githubusercontent.com/assets/1725068/18940649/21945000-8645-11e6-86ed-4a0f800e5a73.png" width="32" height="32" /> <img src="https://cloud.githubusercontent.com/assets/1725068/18940648/2192ddba-8645-11e6-864d-6d5692d55717.png" width="32" height="32" /> <img src="https://user-images.githubusercontent.com/1725068/41266195-ddf767b2-6e30-11e8-9d6b-2adf6a9f57a5.png" width="32" height="32" />

![preemption xx](https://user-images.githubusercontent.com/1725068/41327179-4e839948-6efd-11e8-982b-a670d511e04f.png)

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
