/*
 * Copyright (c) 2009-2018 Arm Limited. All rights reserved.
 * Copyright (c) 2019 Nuclei Limited. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
/*******************************************************************************
 * @file     system_t690.h
 * @brief    NMSIS Nuclei N/NX Device Peripheral Access Layer Header File for
 *           Device T690
 * @version  V1.10
 * @date     30. July 2021
 ******************************************************************************/

#ifndef __SYSTEM_T690_H__   /* TODO: replace '<Device>' with your device name */
#define __SYSTEM_T690_H__

#ifdef __cplusplus
extern "C" {
#endif

extern uint32_t SystemCoreClock;     /*!< System MCore Clock Frequency */

/**
 * \brief Setup the microcontroller system.
 * \details
 *  Initialize the System and update the SystemCoreClock variable.
 */
extern void SystemInit(void);

/**
 * \brief  Update SystemCoreClock variable.
 * \details
 *  Updates the SystemCoreClock with current core Clock retrieved from cpu registers.
 */
extern void SystemCoreClockUpdate(void);

#ifdef __cplusplus
}
#endif

#endif /* __SYSTEM_T690_H__ */
