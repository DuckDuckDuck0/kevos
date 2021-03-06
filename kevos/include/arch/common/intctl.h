/* Copyright 2018 kevin Lau (http://github.com/stormycatcat)

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/

#ifndef _KEVOS_ARCH_COMMON_INTCTL_H_
#define _KEVOS_ARCH_COMMON_INTCTL_H_

#include <sys/types.h>

namespace intr
{

class InterruptController
{
public:
	static void initialize();

	static void enableInterrupts();
	static void disableInterrupts();

	static void sendEndSignal(uint16_t num);

	static void enableTimer();
	static void disableTimer();
	static void setTimerFrequency(uint32_t freq);

	static void enableKeyboard();
	static void disableKeyboard();
};

}

#endif
