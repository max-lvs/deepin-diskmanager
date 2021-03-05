#include "stubAll.h"
#include "../application/partedproxy/dmdbushandler.h"
#include <QDebug>

void start()
{
    qDebug() << "start" << "11111";
}

void getDeviceInfo()
{
    DeviceInfoMap map;
    DeviceInfo devinfo;
    devinfo.m_path = "/dev/sde";
    devinfo.length = 468862128;
    devinfo.heads = 255;
    devinfo.sectors = 63;
    devinfo.cylinders = 29185;
    devinfo.cylsize = 16065;
    devinfo.model = "ATA CT240BX500SSD1";
    devinfo.serial_number = "2002E3E11F2F";
    devinfo.disktype = "gpt";
    devinfo.sector_size = 512;
    devinfo.max_prims = 128;
    devinfo.highest_busy = 7;
    devinfo.readonly = false;
    devinfo.max_partition_name_length = 36;

    PartitionVec partition;
    PartitionInfo partitionInfo1;
    partitionInfo1.m_devicePath = "/dev/sde";
    partitionInfo1.m_partitionNumber = 1;
    partitionInfo1.m_type = 0;
    partitionInfo1.m_status = 0;
    partitionInfo1.m_alignment = 2;
    partitionInfo1.m_fileSystemType = 11;
    partitionInfo1.m_flag = 0;
    partitionInfo1.m_uuid = "23ed0dcd-7dd3-4ddb-87ed-bc1b6102c820";
    partitionInfo1.m_name = "";
    partitionInfo1.m_sectorStart = 2048;
    partitionInfo1.m_sectorEnd = 2099200;
    partitionInfo1.m_sectorsUsed = 101280;
    partitionInfo1.m_sectorsUnused = 1995872;
    partitionInfo1.m_sectorsUnallocated = 1;
    partitionInfo1.m_significantThreshold = 41943;
    partitionInfo1.m_freeSpaceBefore = -1;
    partitionInfo1.m_sectorSize = 512;
    partitionInfo1.m_fileSystemBlockSize = 4096;
    partitionInfo1.m_path = "/dev/sde1";
    partitionInfo1.m_fileSystemLabel = "";
    partitionInfo1.m_insideExtended = false;
    partitionInfo1.m_busy = false;
    partitionInfo1.m_fileSystemReadOnly = false;
    partitionInfo1.m_mountPoints = QVector<QString>();

    PartitionInfo partitionInfo2;
    partitionInfo2.m_devicePath = "/dev/sde";
    partitionInfo2.m_partitionNumber = 2;
    partitionInfo2.m_type = 0;
    partitionInfo2.m_status = 0;
    partitionInfo2.m_alignment = 2;
    partitionInfo2.m_fileSystemType = 11;
    partitionInfo2.m_flag = 0;
    partitionInfo2.m_uuid = "10d06621-db02-4ba8-82a8-03ff5cffb79a";
    partitionInfo2.m_name = "";
    partitionInfo2.m_sectorStart = 2099201;
    partitionInfo2.m_sectorEnd = 4196353;
    partitionInfo2.m_sectorsUsed = 101280;
    partitionInfo2.m_sectorsUnused = 1995872;
    partitionInfo2.m_sectorsUnallocated = 1;
    partitionInfo2.m_significantThreshold = 41943;
    partitionInfo2.m_freeSpaceBefore = -1;
    partitionInfo2.m_sectorSize = 512;
    partitionInfo2.m_fileSystemBlockSize = 4096;
    partitionInfo2.m_path = "/dev/sde2";
    partitionInfo2.m_fileSystemLabel = "";
    partitionInfo2.m_insideExtended = false;
    partitionInfo2.m_busy = false;
    partitionInfo2.m_fileSystemReadOnly = false;
    partitionInfo2.m_mountPoints = QVector<QString>();

    PartitionInfo partitionInfo3;
    partitionInfo3.m_devicePath = "/dev/sde";
    partitionInfo3.m_partitionNumber = -1;
    partitionInfo3.m_type = 3;
    partitionInfo3.m_status = 0;
    partitionInfo3.m_alignment = 2;
    partitionInfo3.m_fileSystemType = 1;
    partitionInfo3.m_flag = 0;
    partitionInfo3.m_uuid = "";
    partitionInfo3.m_name = "";
    partitionInfo3.m_sectorStart = 4196354;
    partitionInfo3.m_sectorEnd = 468862127;
    partitionInfo3.m_sectorsUsed = -1;
    partitionInfo3.m_sectorsUnused = -1;
    partitionInfo3.m_sectorsUnallocated = 0;
    partitionInfo3.m_significantThreshold = 1;
    partitionInfo3.m_freeSpaceBefore = -1;
    partitionInfo3.m_sectorSize = 512;
    partitionInfo3.m_fileSystemBlockSize = -1;
    partitionInfo3.m_path = "unallocated";
    partitionInfo3.m_fileSystemLabel = "";
    partitionInfo3.m_insideExtended = false;
    partitionInfo3.m_busy = false;
    partitionInfo3.m_fileSystemReadOnly = false;
    partitionInfo3.m_mountPoints = QVector<QString>();

    partition.append(partitionInfo1);
    partition.append(partitionInfo2);
    partition.append(partitionInfo3);

    devinfo.partition = partition;

    map.insert("/dev/sde", devinfo);

    DMDbusHandler::instance()->onUpdateDeviceInfo(map);
    qDebug() << "getDeviceInfo";
}

void setCurSelect()
{
    QString devicePath = "/dev/sde";
    QString partitionPath = "sde1";
    Sector start = 2048;
    Sector end = 2099200;
    if (((devicePath != DMDbusHandler::instance()->m_curDevicePath) || (partitionPath != DMDbusHandler::instance()->m_curPartitionPath)) && DMDbusHandler::instance()->m_deviceMap.size() > 0) {
        DMDbusHandler::instance()->m_curDevicePath = devicePath;
        auto it = DMDbusHandler::instance()->m_deviceMap.find(devicePath);
        if (it != DMDbusHandler::instance()->m_deviceMap.end()) {
            for (PartitionInfo info : it.value().partition) {
                if (info.m_sectorStart == start && info.m_sectorEnd == end) {
                    qDebug() << info.m_partitionNumber << info.m_path << Utils::fileSystemTypeToString(static_cast<FSType>(info.m_fileSystemType));
                    DMDbusHandler::instance()->m_curPartitionInfo = info;
                    break;
                }
            }
        }
        DMDbusHandler::instance()->emit curSelectChanged();
    }
}

void setCurSelectSecond()
{
    QString devicePath = "/dev/sde";
    QString partitionPath = "sde2";
    Sector start = 2099201;
    Sector end = 4196353;
    if (((devicePath != DMDbusHandler::instance()->m_curDevicePath) || (partitionPath != DMDbusHandler::instance()->m_curPartitionPath)) && DMDbusHandler::instance()->m_deviceMap.size() > 0) {
        DMDbusHandler::instance()->m_curDevicePath = devicePath;
        auto it = DMDbusHandler::instance()->m_deviceMap.find(devicePath);
        if (it != DMDbusHandler::instance()->m_deviceMap.end()) {
            for (PartitionInfo info : it.value().partition) {
                if (info.m_sectorStart == start && info.m_sectorEnd == end) {
                    qDebug() << info.m_partitionNumber << info.m_path << Utils::fileSystemTypeToString(static_cast<FSType>(info.m_fileSystemType));
                    DMDbusHandler::instance()->m_curPartitionInfo = info;
                    break;
                }
            }
        }
        DMDbusHandler::instance()->emit curSelectChanged();
    }
}

void setCurSelectOcated()
{
    qDebug() << "setCurSelectOcated";
    QString devicePath = "/dev/sde";
    QString partitionPath = "ocated";
    Sector start = 4196354;
    Sector end = 468862127;
    if (((devicePath != DMDbusHandler::instance()->m_curDevicePath) || (partitionPath != DMDbusHandler::instance()->m_curPartitionPath)) && DMDbusHandler::instance()->m_deviceMap.size() > 0) {
        DMDbusHandler::instance()->m_curDevicePath = devicePath;
        auto it = DMDbusHandler::instance()->m_deviceMap.find(devicePath);
        if (it != DMDbusHandler::instance()->m_deviceMap.end()) {
            for (PartitionInfo info : it.value().partition) {
                if (info.m_sectorStart == start && info.m_sectorEnd == end) {
                    qDebug() << info.m_partitionNumber << info.m_path << Utils::fileSystemTypeToString(static_cast<FSType>(info.m_fileSystemType));
                    DMDbusHandler::instance()->m_curPartitionInfo = info;
                    break;
                }
            }
        }
        DMDbusHandler::instance()->emit curSelectChanged();
    }
}

QStringList getAllSupportFileSystem()
{
    QStringList list;
    list << "ext2" << "ext3" << "ext4" << "fat32" << "ntfs";
    return list;
}

void hide()
{
    qDebug() << "hidePartition";
}

void show()
{
    qDebug() << "showPartition";
}

void deletePartition()
{
    qDebug() << "deletePartition";
}

void unmountPartition()
{
    qDebug() << "unmountPartition";
}

void mountPartition()
{
    qDebug() << "mountPartition";
}

void formatPartition()
{
    qDebug() << "formatPartition";
}

void createPartition()
{
    qDebug() << "createPartition";
}

void resizePartition()
{
    qDebug() << "resizePartition";
}

int MessageboxExec()
{
    return 1;
}

HardDiskInfo getDiskInfo()
{
    HardDiskInfo hardDiskInfo;
    hardDiskInfo.m_Model = "Lenovo SSD SL700 240G";
    hardDiskInfo.m_Vendor = "External";
    hardDiskInfo.m_MediaType = "HDD";
    hardDiskInfo.m_Size = "240 GB";
    hardDiskInfo.m_RotationRate = "Solid State Device";
    hardDiskInfo.m_Interface = "USB";
    hardDiskInfo.m_SerialNumber = "LSL70240B073F01636";
    hardDiskInfo.m_Version = "0204";
    hardDiskInfo.m_Capabilities = "";
    hardDiskInfo.m_Description = "disk";
    hardDiskInfo.m_PowerOnHours = "1183";
    hardDiskInfo.m_PowerCycleCount = "1350";
    hardDiskInfo.m_FirmwareVersion = "SBFM61.3";
    hardDiskInfo.m_Speed = "6.0 Gb/s (current: 6.0 Gb/s)";

    return hardDiskInfo;
}

QString filePath()
{
    return "/mnt/DiskInfo";
}

QString emptyFilePath()
{
    return "";
}

QString errorFilePath()
{
    return "/user/DiskInfo.txt";
}

QString noPermissionFilePath()
{
    return "/usr/DiskInfo.txt";
}

QString passedDeviceStatus()
{
    return "PASSED";
}

QString failureDeviceStatus()
{
    return "Failure";
}

QString unknownDeviceStatus()
{
    return "unknown";
}

HardDiskStatusInfoList deviceCheckHealthInfo()
{
    QStringList list;
    list << "1,Raw_Read_Error_Rate,0x000b,100,100,050,Pre-fail,Always,-,0"
         << "9,Power_On_Hours,0x0012,100,100,000,Old_age,Always,,1206"
         << "12,Power_Cycle_Count,0x0012,,100,000,Old_age,Always,In_the_past,1350"
         << "168,Unknown_Attribute,0x0012,100,,000,Old_age,Always,-,0"
         << "170,,0x0003,100,100,000,Pre-fail,Always,FAILING_NOW,474"
         << "173,Unknown_Attribute,0x0012,100,100,,Old_age,Always,-,131075"
         << "192,Power-Off_Retract_Count,0x0012,100,100,000,Old_age,Always,-,"
         << "194,Temperature_Celsius,0x0023,067,067,000,Pre-fail,Always,unknown,33(Min/Max33/33)"
         << "218,Unknown_Attribute,0x000b,100,100,050,Pre-fail,Always,-,0"
         << "231,Temperature_Celsius,0x0013,100,100,000,Pre-fail,Always,-,99"
         << ",Total_LBAs_Written,0x0012,100,100,000,Old_age,Always,-,1334";

    QList<HardDiskStatusInfo> HardDiskStatusInfoList;
    for (int i = 0; i < list.count(); i++) {
        QString str = list.at(i);
        QStringList dataList = str.split(",");

        HardDiskStatusInfo hardDiskStatusInfo;
        hardDiskStatusInfo.m_id = dataList.at(0);
        hardDiskStatusInfo.m_attributeName = dataList.at(1);
        hardDiskStatusInfo.m_flag = dataList.at(2);
        hardDiskStatusInfo.m_value = dataList.at(3);
        hardDiskStatusInfo.m_worst = dataList.at(4);
        hardDiskStatusInfo.m_thresh = dataList.at(5);
        hardDiskStatusInfo.m_type = dataList.at(6);
        hardDiskStatusInfo.m_updated = dataList.at(7);
        hardDiskStatusInfo.m_whenFailed = dataList.at(8);
        hardDiskStatusInfo.m_rawValue = dataList.at(9);

        HardDiskStatusInfoList << hardDiskStatusInfo;
    }

    return HardDiskStatusInfoList;
}

void badSectorsCheck()
{
    qDebug() << "badSectorsCheck";
}

void badSectorsRepair()
{
    qDebug() << "badSectorsRepair";
}
