
If (Form event code:C388=On Load:K2:1)
	
	$c:=Get system colors
	
	OBJECT GET COORDINATES:C663(*; "T0"; $x; $y; $r; $b)
	$h:=$b-$y
	$w:=$r-$x
	
	C_POINTER:C301($NIL)
	$x:=0
	$y:=0
	
	For each ($color; $c)
		
		OBJECT DUPLICATE:C1111(*; "T0"; $color; $NIL; ""; $x; $y; *)
		$y:=$y+$h
		
		OBJECT SET RGB COLORS:C628(*; $color; Choose:C955($c[$color]=0x0000; 0xFFFF; 0x0000); $c[$color])
		
		$hex:=String:C10($c[$color]; "&x")
		$hex:="000000"+Substring:C12($hex; 3)
		$hex:=Substring:C12($hex; Length:C16($hex)-5)
		
		OBJECT SET TITLE:C194(*; $color; $color+" #"+$hex)
		
	End for each 
End if 