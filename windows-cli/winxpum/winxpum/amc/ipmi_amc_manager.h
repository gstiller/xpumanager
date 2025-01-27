/*
 *  Copyright (C) 2021-2023 Intel Corporation
 *  SPDX-License-Identifier: MIT
 *  @file ipmi_amc_manager.h
 */
#pragma once

#include <future>
#include <string>

#include "amc_manager.h"
#include "..\include\xpum_log.h"

using namespace std;
namespace xpum {
class IpmiAmcManager : public AmcManager {
   private:
    bool initialized = false;

    bool initSuccess = false;

    std::mutex mtx;

    std::vector<std::string> amcFwList;

    std::future<xpum_firmware_flash_result_t> task;

    void updateAmcFwList();

    bool fwUpdated = false;

   public:
    virtual bool preInit() override;
    virtual bool init(InitParam& param) override;
    virtual std::string getProtocol() override {
        return "ipmi";
    }
    virtual void flashAMCFirmware(FlashAmcFirmwareParam& param) override;
    virtual void getAmcFirmwareVersions(GetAmcFirmwareVersionsParam& param) override;
    virtual void getAMCFirmwareFlashResult(GetAmcFirmwareFlashResultParam& param) override;
    //virtual void getAMCSensorReading(GetAmcSensorReadingParam& param) override;
    virtual void getAMCSlotSerialNumbers(GetAmcSlotSerialNumbersParam& param) override;
    void getAMCSerialNumberByRiserSlot(uint8_t riser, uint8_t slot, std::string &serialNumber);
};

typedef void (*percent_callback_func_t)(uint32_t percent, void *pAmcManager);

} // namespace xpum