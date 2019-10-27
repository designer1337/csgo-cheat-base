#pragma once

#include <windows.h>
#include <iostream>
#include <cstdint>
#include <memory>
#include <vector>
#include <thread>
#include <chrono>
#include <array>
#include <fstream>
#include <istream>
#include <unordered_map>
#include <intrin.h>
#include <filesystem>

#include "utilities/singleton.hpp"
#include "utilities/fnv.hpp"
#include "utilities/md5/md5.hpp"
#include "utilities/utilities.hpp"
#include "../dependencies/minhook/minhook.h"
#include "interfaces/interfaces.hpp"
#include "../source-sdk/sdk.hpp"
#include "../core/hooks/hooks.hpp"
#include "../dependencies/math/math.hpp"
#include "../dependencies/utilities/renderer/renderer.hpp"
#include "../dependencies/utilities/console/console.hpp"
#include "utilities/csgo.hpp"