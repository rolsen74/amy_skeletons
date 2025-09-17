# AmigaOS4 Skeletons

Skeleton templates for creating AmigaOS4 libraries and devices.

**Variants:**
- **68k** — Includes jumptable stubs for AmigaOS3 (68k)
- **Normal** — Manual registration into the system (more control/freedom)
- **Autoinit** — Automatically added by the system
- **Library** — Builds an Amiga library
- **Device** — Builds an Amiga device

**Notes:**
1. Include files are manually created because `bumprev`/`idltool` are Amiga-only tools, and they add a Hyperion copyright
   notice, which would place them in unknown copyright territory for us.
2. Some directories are empty for now — they are placeholders to show the intended layout and will be filled over time.

— Rene W. Olsen (17-Sep-2025)

**License:** [Unlicense](LICENSE) — Public Domain

---

## 🧩 Generic Libraries
- `_Generic_Library_Normal`
- `_Generic_Library_Normal_68k`
- `_Generic_Library_Autoinit`
- `_Generic_Library_Autoinit_68k`

## ⚙️ Generic Devices
- `_Generic_Device_Normal`
- `_Generic_Device_Normal_68k`
- `_Generic_Device_Normal_Main`
- `_Generic_Device_Normal_Main_68k`
- `_Generic_Device_Autoinit`
- `_Generic_Device_Autoinit_68k`

## 💾 Example Libraries
- `lib_Blanker` — Example blanker library
- `lib_Gadget` — Example gadget class library

## 🖨️ Example Devices
- `dev_Printer` — Example printer device (Parallel.dev)
- `dev_SANA2` — Example Ethernet device
- `dev_Trackdisk` — Example disk device

---
