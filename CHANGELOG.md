# Changelog

All notable changes to this project will be documented in this file. See [standard-version](https://github.com/conventional-changelog/standard-version) for commit guidelines.

## [0.2.0](https://github.com/Nick-Fanelli/HarmonyEngine/compare/v0.1.1...v0.2.0) (2021-03-19)


### ⚠ BREAKING CHANGES

* move all render and imgui related stuff to EditorLayers files to maintain
* migrated the Playsapce over to new HarmonyEditor project
* overhaul the entire game object system with new entity system

### Features

* implement all macros for input ([65f1443](https://github.com/Nick-Fanelli/HarmonyEngine/commit/65f1443b7d1449970ecbfe352da18556218e0510))
* implement assertions ([46a9156](https://github.com/Nick-Fanelli/HarmonyEngine/commit/46a915644070883d1491174225b248c8d6d62cf9))
* implement basic custom dark-theme ([f3403ce](https://github.com/Nick-Fanelli/HarmonyEngine/commit/f3403ce0ae039da78a0292b4dd9f44115b5073af))
* implement basic theme change support ([6a63036](https://github.com/Nick-Fanelli/HarmonyEngine/commit/6a63036513b6fdb73d5ba81da2f511b18fa0fe4f))
* implement basic theme support with ability to programatically set the theme from light to dark (light colors not implemented yet) ([a1a9a90](https://github.com/Nick-Fanelli/HarmonyEngine/commit/a1a9a90d62a9900786cd02e35b0cb776a8be94a1))
* implement frame rounding nad window border size ([115f30b](https://github.com/Nick-Fanelli/HarmonyEngine/commit/115f30b265262d50eddfdda27b9f7d1afe5097eb))
* implement new versions of Transform and QuadRenderer component ([9917d3e](https://github.com/Nick-Fanelli/HarmonyEngine/commit/9917d3e9e3de598d848bbe8e4fffd1705655318b))
* implement overload for entt::entity to ostream for logging ([f8ff68a](https://github.com/Nick-Fanelli/HarmonyEngine/commit/f8ff68a3d5564987d5b8b2e54952e29d4206d437))
* light theme colors ([f8bd236](https://github.com/Nick-Fanelli/HarmonyEngine/commit/f8bd23664a295df28e075f02e53706be7962e444))
* setup basic dockspace ([9dcc02e](https://github.com/Nick-Fanelli/HarmonyEngine/commit/9dcc02ed79960794a47fd886fd69925b50dc841a))
* vertex count and index count to renderer statistics ([63ae520](https://github.com/Nick-Fanelli/HarmonyEngine/commit/63ae5206fd4470cf630325f96591232500bd32b1))


### Bug Fixes

* add getter for scene registry and and update that in the entity file ([95c74c7](https://github.com/Nick-Fanelli/HarmonyEngine/commit/95c74c70462d69098f4aadc80c95551448449dfd))
* mark HierarchalNode constructor as explicit ([ef5a33a](https://github.com/Nick-Fanelli/HarmonyEngine/commit/ef5a33a5ac61b7cef32dee785678892d6798a4a7))
* remove gameContext argument from renderlayer and set RenderLayer::s_Scene to nullptr to start ([443b3f3](https://github.com/Nick-Fanelli/HarmonyEngine/commit/443b3f3d9e6db5bd7e8f4dcb213a51c5b4d6c2ab))
* remove the duplicate and unnessesary entt include because it is auto-included with harmonypch.h ([bbef9ab](https://github.com/Nick-Fanelli/HarmonyEngine/commit/bbef9abd1287ffb4a7f1d5032d7c499233d70dfc))
* render scene before ImGui so that ImGui is on top ([680e723](https://github.com/Nick-Fanelli/HarmonyEngine/commit/680e723ec916f1358e4a56d4f5ea1f4d254b84fe))
* separator colors ([b916d85](https://github.com/Nick-Fanelli/HarmonyEngine/commit/b916d85f450a9982404c0ec1e52ad879ac4a5d2f))
* update docking preivew color to accent color ([c9f3253](https://github.com/Nick-Fanelli/HarmonyEngine/commit/c9f3253574c5f955a8100b8ac89091b0f809e33d))
* window color when docking ([188005f](https://github.com/Nick-Fanelli/HarmonyEngine/commit/188005f57935b3c605841f57e4fa608dc716df5f))


* migrated the Playsapce over to new HarmonyEditor project ([c751e9c](https://github.com/Nick-Fanelli/HarmonyEngine/commit/c751e9c380c0d95cdcec2152673a9f9565bfdc0c))
* move all render and imgui related stuff to EditorLayers files to maintain ([e1f846a](https://github.com/Nick-Fanelli/HarmonyEngine/commit/e1f846ae74291bd8f963381e1190fd5914804eb1))
* overhaul the entire game object system with new entity system ([44c8393](https://github.com/Nick-Fanelli/HarmonyEngine/commit/44c83936021506aec3ccb836d8df8692ebce0dd7))

### [0.1.1](https://github.com/Nick-Fanelli/HarmonyEngine/compare/v0.1.0...v0.1.1) (2021-03-02)


### Features

* implement basic imgui boiler-plate code ([597afd9](https://github.com/Nick-Fanelli/HarmonyEngine/commit/597afd993d2e8d94f03c498c7202911177b9e03c))
* implement basic imgui to editor scene ([2da429b](https://github.com/Nick-Fanelli/HarmonyEngine/commit/2da429bb688258298b8b85a57f20f82f8ff73627))
* implement basic sprite header ([bac4306](https://github.com/Nick-Fanelli/HarmonyEngine/commit/bac4306fb93de215996ec5ad8ad318b903670e66))
* implement imgui renderer implementation ([ece22f3](https://github.com/Nick-Fanelli/HarmonyEngine/commit/ece22f3e2b7feb99a098abc781a993ded9ae0338))


### Bug Fixes

* add imgui license ([f372d1e](https://github.com/Nick-Fanelli/HarmonyEngine/commit/f372d1e6baa1b9b79b1cdb7ce4e83f39a8cc99fe))
* add the include directory in the HarmonyEngine project as target_include_directory ([3ba3f84](https://github.com/Nick-Fanelli/HarmonyEngine/commit/3ba3f8421f67913014a28ca24c624134dd8accf1))

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
