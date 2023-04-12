![version](https://img.shields.io/badge/version-19%2B-5682DF)
![platform](https://img.shields.io/static/v1?label=platform&message=mac-intel%20|%20mac-arm&color=blue)
[![license](https://img.shields.io/github/license/miyako/4d-plugin-get-system-colors)](LICENSE)
![downloads](https://img.shields.io/github/downloads/miyako/4d-plugin-get-system-colors/total)

# 4d-plugin-get-system-colors
for macOS (10.13 SDK before dark mode & 10.14 SDK)

* get `controlAccentColor` in `deviceRGBColorSpace` 

```4d
$colors:=Get system colors
$controlAccentColor:=$colors.controlAccentColor
```

* blend `controlAccentColor` with another color and fraction (between `0` to `1`)

```4d
$colors:=Get system colors(Blend with windowBackgroundColor; 0.7)
$controlAccentColor:=$colors.controlAccentColor
$colors:=Get system colors(Blend with whiteColor; 0.5)
$controlAccentColor:=$colors.controlAccentColor
$colors:=Get system colors(Blend with blackColor; 0.3)
$controlAccentColor:=$colors.controlAccentColor
```

* blend `controlAccentColor` with custom color and fraction (between `0` to `1`)

```4d
$colors:=Get system colors(0x00FF0000; 0.5)
$controlAccentColor:=$colors.controlAccentColor
```
