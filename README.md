![version](https://img.shields.io/badge/version-19%2B-5682DF)
![platform](https://img.shields.io/static/v1?label=platform&message=mac-intel%20|%20mac-arm&color=blue)
[![license](https://img.shields.io/github/license/miyako/4d-plugin-get-system-colors)](LICENSE)
![downloads](https://img.shields.io/github/downloads/miyako/4d-plugin-get-system-colors/total)

# 4d-plugin-get-system-colors

This plugin exposes macOS's AppKit system color palette (`NSColor`'s built-in "system colors" — the colors AppKit itself uses for controls, text, windows, and highlights) to 4D as a single command, `Get system colors`, which returns an `Object` whose properties are the individual color values. Every value is a packed device-RGB integer (`0x00RRGGBB`), read via `NSColorSpace.deviceRGBColorSpace`, exactly as `NSColor`'s system palette reports it on the machine 4D is running on — including automatic light/dark-mode variation, since these are the live AppKit colors, not fixed constants. The plugin can optionally blend every returned color toward another color (a named system color, or an arbitrary RGB value you supply) by a fraction you choose.

## Summary table

| Command | Returns | Purpose |
|---|---|---|
| [`Get system colors`](#get-system-colors) | Object | Returns the current AppKit system color palette, optionally blended toward another color |

**Platforms:** macOS only (Intel and Apple Silicon). There is no Windows implementation — the plugin's C++ source contains no `#if VERSIONWIN` branch at all; every color comes from `NSColor`/AppKit, a macOS-only framework.

---

## Requirements & platform notes

- **macOS 10.13+** for the base color set, including `findHighlightColor`.
- **macOS 10.14+ (Mojave, "Dark Mode")** for `controlAccentColor`, `selectedContentBackgroundColor`, `separatorColor`, `unemphasizedSelectedContentBackgroundColor`, `unemphasizedSelectedTextColor`, and `unemphasizedSelectedTextBackgroundColor`. On macOS 10.13, the returned object simply omits these six properties — there's no error, no placeholder value, they're absent from the object entirely.
- The command takes **no mandatory parameters**. Both parameters are optional (confirmed by the plugin's own sample method, `TEST.4dm`, which calls it with zero, and with one, parameter — see the Example section below).
- Every value in the returned object is a **Longint** holding a packed `0x00RRGGBB` color, not a 4D `Picture` or a `#RRGGBB` string.
- The color values reflect **live system state** at the moment the command runs — including whatever appearance (Light/Dark) the calling process is currently in — they are not fixed/cached constants baked into the plugin.

---

## Get system colors

### Syntax

```
Get system colors { ( blendMode|blendColor : Longint ; fraction : Real ) } -> Result : Object
```

### Parameters

| Parameter | Type | Description |
|---|---|---|
| `blendMode`\|`blendColor` | Longint | Optional. Either one of the plugin's named blend-mode constants (`Blend with windowBackgroundColor`, `Blend with whiteColor`, `Blend with blackColor`), or an arbitrary packed `0x00RRGGBB` Longint to blend toward a custom color instead. Omit it (or pass nothing) to get each color's raw, unblended value. |
| `fraction` | Real | Optional. How far to blend toward `blendMode`/`blendColor`, from `0` (no change) to `1` (fully replaced by the blend target). Out-of-range values are clamped into `0…1`; a non-numeric (NaN/Infinity) value is treated as `0`. Omit it to use `0`. |
| Result | Object | Every property is a system color name (see the table below) whose value is a Longint packed device-RGB color (`0x00RRGGBB`). |

### Description

Called with no parameters, `Get system colors` returns every system color exactly as AppKit currently reports it — no blending applied.

Passing `blendMode`/`blendColor` and `fraction` blends **every** color in the result toward the same target color by the same fraction, before it's packed into the result. This isn't a per-color choice — the whole palette is blended uniformly in a single call.

The `blendMode`/`blendColor` parameter is overloaded: the three named constants shown in the plugin's own README and sample method (`Blend with windowBackgroundColor`, `Blend with whiteColor`, `Blend with blackColor`) select one of AppKit's own dynamic colors as the blend target (so, for example, blending toward `windowBackgroundColor` tracks Light/Dark mode automatically). Any other Longint is instead interpreted directly as a packed `0x00RRGGBB` color to blend toward. This dual meaning is inherent to the plugin's design (confirmed from source), but the exact underlying integer values of the three named constants weren't available to verify against this documentation pass — in the unlikely event you construct a custom blend color that happens to collide with one of them, you'd get the named dynamic color instead of your literal one. If you need to rule this out for a specific value, check with the plugin author or test the specific value directly.

The returned object's property set is **not identical across macOS versions** — see Requirements & platform notes above for exactly which six properties depend on macOS 10.14+.

**Return-value guarantee:** the command always returns an Object, on every call, including if something goes wrong internally partway through — you'll get whatever properties were already computed rather than 4D waiting indefinitely for a result. (This is true of the plugin's current fixed source; older binaries built before this guarantee was added could theoretically leave a call hanging on an internal failure. If you're not sure which you have, rebuild from the latest source.)

### Result object properties

Every property below is a Longint packed as `0x00RRGGBB`.

| Property | Minimum macOS |
|---|---|
| `controlShadowColor` | 10.13 |
| `controlDarkShadowColor` | 10.13 |
| `controlColor` | 10.13 |
| `controlHighlightColor` | 10.13 |
| `controlLightHighlightColor` | 10.13 |
| `controlTextColor` | 10.13 |
| `controlBackgroundColor` | 10.13 |
| `controlAccentColor` | **10.14** |
| `selectedControlColor` | 10.13 |
| `secondarySelectedControlColor` | 10.13 |
| `selectedControlTextColor` | 10.13 |
| `disabledControlTextColor` | 10.13 |
| `textColor` | 10.13 |
| `textBackgroundColor` | 10.13 |
| `selectedTextColor` | 10.13 |
| `selectedTextBackgroundColor` | 10.13 |
| `gridColor` | 10.13 |
| `keyboardFocusIndicatorColor` | 10.13 |
| `windowBackgroundColor` | 10.13 |
| `underPageBackgroundColor` | 10.13 |
| `labelColor` | 10.13 |
| `secondaryLabelColor` | 10.13 |
| `tertiaryLabelColor` | 10.13 |
| `quaternaryLabelColor` | 10.13 |
| `scrollBarColor` | 10.13 |
| `knobColor` | 10.13 |
| `selectedKnobColor` | 10.13 |
| `windowFrameColor` | 10.13 |
| `windowFrameTextColor` | 10.13 |
| `selectedMenuItemColor` | 10.13 |
| `selectedMenuItemTextColor` | 10.13 |
| `highlightColor` | 10.13 |
| `shadowColor` | 10.13 |
| `headerColor` | 10.13 |
| `headerTextColor` | 10.13 |
| `alternateSelectedControlColor` | 10.13 |
| `alternateSelectedControlTextColor` | 10.13 |
| `scrubberTexturedBackgroundColor` | 10.13 |
| `placeholderTextColor` | 10.13 |
| `linkColor` | 10.13 |
| `findHighlightColor` | 10.13 |
| `selectedContentBackgroundColor` | **10.14** |
| `separatorColor` | **10.14** |
| `unemphasizedSelectedContentBackgroundColor` | **10.14** |
| `unemphasizedSelectedTextColor` | **10.14** |
| `unemphasizedSelectedTextBackgroundColor` | **10.14** |

### Example

From the plugin's own test method (`TEST.4dm`):

```4d
//%attributes = {}
$colors:=Get system colors
$controlAccentColor:=$colors.controlAccentColor  //31487

$colors:=Get system colors(Blend with windowBackgroundColor)
$controlAccentColor:=$colors.controlAccentColor  //15527148

$colors:=Get system colors(Blend with blackColor)
$controlAccentColor:=$colors.controlAccentColor
```

Reading one property at a time, with an explicit fraction:

```4d
$colors:=Get system colors(Blend with windowBackgroundColor; 0.7)
$controlAccentColor:=$colors.controlAccentColor
```

Blending toward a custom color instead of a named one — here, pure red (`0x00FF0000`) at 50%:

```4d
$colors:=Get system colors(0x00FF0000; 0.5)
$controlAccentColor:=$colors.controlAccentColor
```

Reading every property generically, without naming each one — useful if you want to log or inspect the whole palette:

```4d
$colors:=Get system colors
$names:=OB Keys($colors)
For each ($name; $names)
	$value:=$colors[$name]  //Longint, 0x00RRGGBB
End for each
```

Guarding for a property that's only present on macOS 10.14+:

```4d
$colors:=Get system colors
If (OB Instance of($colors; Is object) & (OB Is defined($colors; "controlAccentColor")))
	$accent:=$colors.controlAccentColor
Else
	$accent:=$colors.controlColor  //fall back to a color available since 10.13
End if
```

---

## Error handling & troubleshooting

- **A property is missing from the result.** This means you're on macOS 10.13 and asked for one of the six macOS 10.14+-only properties (see the table above) — it isn't a bug, the property is genuinely absent on that OS version rather than set to a default/empty value.
- **Colors look different than expected after using a "Blend with..." mode.** The three named blend targets (`windowBackgroundColor`, `whiteColor`, `blackColor`) are AppKit's own dynamic colors, so they — and therefore your blended result — change with Light/Dark mode and any system accent-color/appearance setting. This is expected: the plugin always reads the live system palette, it doesn't cache a fixed snapshot.
- **A blend using a raw custom color came back looking like a named blend mode instead.** As noted in the command description, the blend parameter doubles as both an enum selector and a raw packed color; a custom value that happens to collide with one of the three named constants' underlying values would be read as that named mode. This is a real but unverified edge case (the underlying constant values weren't available to check) — worth testing directly if you rely on a specific low-numbered custom blend color.
- **The command never appears to hang**, even if something goes wrong internally reading a particular color — the current source always returns an object rather than leaving 4D waiting. If you're using an older prebuilt binary and see the plugin appear to freeze on this command, that's a signal to rebuild from the latest source.
- **No Windows behavior to fall back on.** This is a macOS-only plugin; there's no equivalent command or partial support on Windows.

---

## Quick reference

```4d
// Raw palette, no blending
$colors:=Get system colors
$accent:=$colors.controlAccentColor

// Blend every color 70% toward the window background (tracks Light/Dark mode)
$colors:=Get system colors(Blend with windowBackgroundColor; 0.7)

// Blend every color 50% toward a custom RGB color
$colors:=Get system colors(0x00FF0000; 0.5)

// Walk every returned color generically
$colors:=Get system colors
For each ($name; OB Keys($colors))
	$value:=$colors[$name]
End for each
```
