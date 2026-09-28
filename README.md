# QMK Userspace

This repository contains Ness's custom QMK userspace configuration, keymaps, and keyboard definitions used to build **wired** firmware for personal keyboards, including the Nest keyboard family (Crane, Egret, Raven) as well as boards like the Charybdis and TBK Mini.

## Related Repositories

- **Keyboard PCBs & Design Files**: [nest_keyboards](https://github.com/fishjord/nest_keyboards) — Hardware designs, schematics, KiCad PCB files, Ergogen configs, and 3D-printable cases/plates for the Nest keyboard family.
- **Wireless Firmware (ZMK)**: [zmk-config](https://github.com/fishjord/zmk-config) — ZMK configurations, shields, and keymaps for building wireless Bluetooth firmware.

## Architecture: Custom Keyboard Definitions & Symlinking

Standard QMK userspace repositories typically only store custom user keymaps (`keyboards/<keyboard>/keymaps/<user>/`) and shared user code (`users/<user>/`), relying on the core `qmk_firmware` repository for all keyboard hardware definitions (pinouts, matrix configuration, `info.json`, `rules.mk`).

In this repository, custom keyboard definitions are stored directly within userspace under [`keyboards/nest/`](keyboards/nest/). To allow standard QMK tools and GitHub Actions to compile targets for these keyboards without maintaining a heavy fork of the entire `qmk_firmware` repository, the keyboard definition directory is symlinked into `qmk_firmware`:

```bash
# Example: Link the Nest keyboard tree into your local qmk_firmware clone
ln -s "$(realpath keyboards/nest)" /path/to/qmk_firmware/keyboards/nest
```

This approach keeps hardware definitions and personal keymaps version-controlled together in userspace while compiling cleanly against upstream `qmk_firmware`.

## Howto configure your build targets

1. Run the normal `qmk setup` procedure if you haven't already done so -- see [QMK Docs](https://docs.qmk.fm/#/newbs) for details.
1. Fork this repository
1. Clone your fork to your local machine
1. Enable userspace in QMK config using `qmk config user.overlay_dir="$(realpath qmk_userspace)"`
1. Add a new keymap for your board using `qmk new-keymap`
    * This will create a new keymap in the `keyboards` directory, in the same location that would normally be used in the main QMK repository. For example, if you wanted to add a keymap for the Planck, it will be created in `keyboards/planck/keymaps/<your keymap name>`
    * You can also create a new keymap using `qmk new-keymap -kb <your_keyboard> -km <your_keymap>`
    * Alternatively, add your keymap manually by placing it in the location specified above.
    * `layouts/<layout name>/<your keymap name>/keymap.*` is also supported if you prefer the layout system
1. Add your keymap(s) to the build by running `qmk userspace-add -kb <your_keyboard> -km <your_keymap>`
    * This will automatically update your `qmk.json` file
    * Corresponding `qmk userspace-remove -kb <your_keyboard> -km <your_keymap>` will delete it
    * Listing the build targets can be done with `qmk userspace-list`
1. Commit your changes

## Howto build with GitHub

1. In the GitHub Actions tab, enable workflows
1. Push your changes above to your forked GitHub repository
1. Look at the GitHub Actions for a new actions run
1. Wait for the actions run to complete
1. Inspect the Releases tab on your repository for the latest firmware build

## Howto build locally

1. Run the normal `qmk setup` procedure if you haven't already done so -- see [QMK Docs](https://docs.qmk.fm/#/newbs) for details.
1. Fork this repository
1. Clone your fork to your local machine
1. `cd` into this repository's clone directory
1. Set global userspace path: `qmk config user.overlay_dir="$(realpath .)"` -- you MUST be located in the cloned userspace location for this to work correctly
    * This will be automatically detected if you've `cd`ed into your userspace repository, but the above makes your userspace available regardless of your shell location.
1. Compile normally: `qmk compile -kb your_keyboard -km your_keymap` or `make your_keyboard:your_keymap`

Alternatively, if you configured your build targets above, you can use `qmk userspace-compile` to build all of your userspace targets at once.

## Extra info

If you wish to point GitHub actions to a different repository, a different branch, or even a different keymap name, you can modify `.github/workflows/build_binaries.yml` to suit your needs.

To override the `build` job, you can change the following parameters to use a different QMK repository or branch:
```
    with:
      qmk_repo: qmk/qmk_firmware
      qmk_ref: master
```

If you wish to manually manage `qmk_firmware` using git within the userspace repository, you can add `qmk_firmware` as a submodule in the userspace directory instead. GitHub Actions will automatically use the submodule at the pinned revision if it exists, otherwise it will use the default latest revision of `qmk_firmware` from the main repository.

This can also be used to control which fork is used, though only upstream `qmk_firmware` will have support for external userspace until other manufacturers update their forks.

1. (First time only) `git submodule add https://github.com/qmk/qmk_firmware.git`
1. (To update) `git submodule update --init --recursive`
1. Commit your changes to your userspace repository
