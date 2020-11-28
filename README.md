## Old schoold demo effects for GD32V

![ESP effects](https://appelsiini.net/img/2020/esp-effects.jpg)

Created to test the [HAGL graphics library](https://github.com/tuupola/hagl). For quick reference see the [recording on Vimeo](https://vimeo.com/419551395). To compile you need [Nuclei SDK](https://doc.nucleisys.com/nuclei_sdk/quickstart.html#quickstart-get-set-nuclei-sdk) and [RISC-V GNU toolchain](https://doc.nucleisys.com/nuclei_sdk/quickstart.html#setup-tools-and-environment).

```
$ git clone git@github.com:Nuclei-Software/nuclei-sdk.git
$ git clone git@github.com:tuupola/gd32v_effects.git --recursive
$ cd gd32v_effects
$ make SOC=gd32vf103 BOARD=gd32vf103c_longan_nano upload
```

## Run on computer

HAGL is hardware agnostic. You can run the demos also [on your computer](https://github.com/tuupola/sdl2_effects).

