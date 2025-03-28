#include "stm_flash.h"
#include "stm32f1xx_hal_flash_ex.h"

//读指定地址的半字(16位数据)
uint16_t FLASH_ReadHalfWord(uint32_t addr)
{
		return *(__IO uint16_t*)addr;
}

// 读取指定地址的单字(32位数据)
uint32_t FLASH_ReadWord(uint32_t address)
{
    return *(__IO uint32_t*)address;
}

// 读取指定地址的双字(64位数据)
uint64_t FLASH_ReadDoubleWord(uint32_t address)
{
    return *(__IO uint64_t*)address;
}

// 从指定地址开始读取多个数据（16位数据）
void FLASH_ReadHalfWordData(uint32_t startAddress, uint16_t *readData, uint16_t countToRead)
{
    uint16_t dataIndex;
    for (dataIndex = 0; dataIndex < countToRead; dataIndex++)
    {
        readData[dataIndex] = FLASH_ReadHalfWord(startAddress + dataIndex * 2);
    }
}

// 从指定地址开始读取多个数据（32位数据）
void FLASH_ReadWordData(uint32_t startAddress, uint32_t *readData, uint16_t countToRead)
{
    uint16_t dataIndex;
    for (dataIndex = 0; dataIndex < countToRead; dataIndex++)
    {
        readData[dataIndex] = FLASH_ReadWord(startAddress + dataIndex * 4);
    }
}

// 从指定地址开始读取多个数据（64位数据）
void FLASH_ReadDoubleWordData(uint32_t startAddress, uint64_t *readData, uint16_t countToRead)
{
    uint16_t dataIndex;
    for (dataIndex = 0; dataIndex < countToRead; dataIndex++)
    {
        readData[dataIndex] = FLASH_ReadDoubleWord(startAddress + dataIndex * 8);
    }
}

//Flash写入
void Flash_Write(uint32_t address, uint16_t *data, uint16_t length) {
    HAL_FLASH_Unlock();
    
    // 擦除需要的页
    FLASH_EraseInitTypeDef EraseInitStruct;
    uint32_t PageError = 0;
    
    EraseInitStruct.TypeErase = FLASH_TYPEERASE_PAGES;
    EraseInitStruct.PageAddress = address;
    EraseInitStruct.NbPages = ((length * 2) + FLASH_PAGE_SIZE - 1) / FLASH_PAGE_SIZE;
    
    if (HAL_FLASHEx_Erase(&EraseInitStruct, &PageError) != HAL_OK) {
        // 擦除错误处理
        HAL_FLASH_Lock();
        return;
    }
    
    // 写入数据
    for(uint16_t i = 0; i < length; i++) {
        if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, 
                             address + (i * 2), 
                             data[i]) != HAL_OK) {
            // 写入错误处理
            break;
        }
    }
    
    HAL_FLASH_Lock();
}
