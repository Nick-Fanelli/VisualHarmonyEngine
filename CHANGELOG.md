# Changelog

All notable changes to this project will be documented in this file. See [standard-version](https://github.com/conventional-changelog/standard-version) for commit guidelines.

## 0.1.0 (2021-02-20)


### ⚠ BREAKING CHANGES

* update all engine files to use the new precompiled header
* use namespace HarmonyEngine across all engine code to keep the dependencies managed
* add separation of projects with the new Playspace project that uses HarmonyEngine

### Features

* add in precompiled header for harmony ([e526298](https://github.com/Nick-Fanelli/HarmonyEngine/commit/e52629813339399ca80744615653a9ea8cad4188))
* add in the npm automatic change log ([a658202](https://github.com/Nick-Fanelli/HarmonyEngine/commit/a658202943fcfb4396dfae0df86a9d3b84e81cd9))
* add SpriteSheet class that can be created and assigned to a quad ([8fa1315](https://github.com/Nick-Fanelli/HarmonyEngine/commit/8fa131545fabf8c27203811d473ace0ea5d66059))


### Bug Fixes

* call renderer.OnDestroy() when the TestScene gets destroyed ([78fc158](https://github.com/Nick-Fanelli/HarmonyEngine/commit/78fc1586b1c523dec9f603291262baaeaf3d08a4))
* explicitly create vertex objects inside Quad structure ([e9e781d](https://github.com/Nick-Fanelli/HarmonyEngine/commit/e9e781d3595e40f1ff90f98f942fb156e57a3e6f))
* renderer is now held inside the game context and is no longer static ([7afe25e](https://github.com/Nick-Fanelli/HarmonyEngine/commit/7afe25ec77836b67ca11f38d77e13300b06d58fa))


* add separation of projects with the new Playspace project that uses HarmonyEngine ([a4085c6](https://github.com/Nick-Fanelli/HarmonyEngine/commit/a4085c61e70baed30b2d02ad6ada24e27fca5304))
* update all engine files to use the new precompiled header ([96228bf](https://github.com/Nick-Fanelli/HarmonyEngine/commit/96228bf952fe421f0ba9ff8ace09ad5803e63382))
* use namespace HarmonyEngine across all engine code to keep the dependencies managed ([123b81e](https://github.com/Nick-Fanelli/HarmonyEngine/commit/123b81e608eb11b64d92a541e8d0b8de4a4f4dde))
