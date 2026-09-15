If (FORM Event:C1606.code=On Load:K2:1)
	
	$colors:=Get system colors
	$controlAccentColor:=$colors.controlAccentColor
	
	OBJECT SET RGB COLORS:C628(*; "r1"; Choose:C955($controlAccentColor=0x0000; 0xFFFF; 0x0000); $controlAccentColor)
	
	$colors:=Get system colors(Blend with windowBackgroundColor; 0.7)
	$controlAccentColor:=$colors.controlAccentColor
	
	OBJECT SET RGB COLORS:C628(*; "r2"; Choose:C955($controlAccentColor=0x0000; 0xFFFF; 0x0000); $controlAccentColor)
	
	$colors:=Get system colors(Blend with whiteColor; 0.5)
	$controlAccentColor:=$colors.controlAccentColor
	
	OBJECT SET RGB COLORS:C628(*; "r3"; Choose:C955($controlAccentColor=0x0000; 0xFFFF; 0x0000); $controlAccentColor)
	
	$colors:=Get system colors(Blend with blackColor; 0.3)
	$controlAccentColor:=$colors.controlAccentColor
	
	OBJECT SET RGB COLORS:C628(*; "r4"; Choose:C955($controlAccentColor=0x0000; 0xFFFF; 0x0000); $controlAccentColor)
	
	$colors:=Get system colors(0x00FF0000; 0.5)
	$controlAccentColor:=$colors.controlAccentColor
	
	OBJECT SET RGB COLORS:C628(*; "r5"; Choose:C955($controlAccentColor=0x0000; 0xFFFF; 0x0000); $controlAccentColor)
	
End if 