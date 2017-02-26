/******************************************************************
 *
 * Copyright 2016 Samsung Electronics All Rights Reserved.
 *
 *
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      LICENSE-2.0" target="_blank">http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 *
 ******************************************************************/
#ifndef PMCsdkHelper_H_
#define PMCsdkHelper_H_

#include "PMCsdkUtilityHelper.h"

#define DASH "-"
#define g_ctx "Provision Manager Client Application Context"
#define ctxProvCreadential "ProvisionCredentials Context"
#define ctxProvPairwise "ctxProvPairwise"
#define ctxProvDirectPairing "ctxProvDirectPairing"
#define ctxUnlinkDevice "ctxUnlinkDevice"
#define ctxRemoveDevice "ctxRemoveDevice"
#define RANDOM_PIN_TEXT_FILE "server_pincode.txt"
#define PIN_MAX_SIZE 9
#define MAX_TIME_INPUT_PROMPT_FOR_PASSWORD 5
#define DEVICE_INDEX_ONE 1
#define DEVICE_INDEX_TWO 2

/*
 * ACL Releated Resources
 */
#define DEFAULT_SUBJECT_UUID "*"
#define ACL_RESOURCE_LEN 2
#define DEAFULT_RESOURCE_URI "*"
#define DEFAULT_RESOURCE_TYPE "*"
#define DEAFULT_INTERFACE_TYPE "*"
#define DEAFULT_ROWNER_UUID "*"

#define ACL_RESRC_MAX_NUM   16
#define ACL_RESRC_MAX_LEN   128
#define ACL_PEMISN_CNT      5
#define DEFAULT_DP_PROVSIONING_PIN "00000000"
#define DEFAULT_DP_PROVSIONING_PIN2 "00000011"
#define FULL_PERMISSION 31
#define NO_PERMISSION 0
#define MAX_PERMISSION_RANGE 65535

#define ACL_RESOURCE_URI "*"
#define ACL_RESOURCE_LENGTH 6 // Check ACL_RESOURCE_NAME for the length. ACL_RESOURCE_LENGTH = len(ACL_RESOURCE_URI) + 1
#define ACL_RES_TYPE_NAME "light"
#define ACL_RES_IF_TYPE_NAME "sensor"

/*
 * Ownership Transfer Related Resource
 */
#define OTM_INVALID_LOBV -1
#define OTM_INVALID_UOBV 10
#define OTM_NONE 0
#define OTM_JUSTWORK 1
#define OTM_RANDOMPIN 2
#define OTM_ALL 3

/*
 * Credential Representative value
 */
#define SYM_PAIR_WISE_KEY 1
#define CRED_TYPE_UOBV 30
#define CRED_TYPE_LOBV -3

// function declaration(s) for calling them before implementing
FILE* fopenProvManager(const char*, const char*);

OicSecAcl_t* createAcl(const int dev_num, int permission, OCProvisionDev_t** m_own_list);
OicSecPdAcl_t* createPdAcl(int nPermission);
OTMCallbackData_t otmCbRegister(int otmType);
int waitCallbackRet(void);

/**
 * Helper Class for Provisioning Manager
 */
class PMCsdkHelper
{
private:
    std::string m_failureMessage;

public:

    PMCsdkHelper();
    bool initProvisionClient(int clientOTMType = OTM_JUSTWORK, char* chDBPath =
            (char*) PRVN_DB_FILE_NAME);
    bool discoverAllDevices(int nTime, OCProvisionDev_t** own_list, OCProvisionDev_t** unown_list,
            OCStackResult expectedResult);
    bool discoverUnownedDevices(int nTime, OCProvisionDev_t** unown_list,
            OCStackResult expectedResult);
    bool discoverOwnedDevices(int nTime, OCProvisionDev_t** own_list, OCStackResult expectedResult);
    bool doOwnerShipTransfer(void *ctx, OCProvisionDev_t** unown_list,
            OCProvisionResultCB resultCallback, OCStackResult expectedResult, bool checkCallback = true);
    bool provisionACL(void* ctx, const OCProvisionDev_t* selectedDeviceInfo, OicSecAcl_t *acl,
            OCProvisionResultCB resultCallback, OCStackResult expectedResult);
    bool provisionCredentials(void *ctx, OicSecCredType_t type, size_t keySize,
            const OCProvisionDev_t *pDev1, const OCProvisionDev_t *pDev2,
            OCProvisionResultCB resultCallback, OCStackResult expectedResult);
    bool provisionPairwiseDevices(void* ctx, OicSecCredType_t type, size_t keySize,
            const OCProvisionDev_t *pDev1, OicSecAcl_t *pDev1Acl, const OCProvisionDev_t *pDev2,
            OicSecAcl_t *pDev2Acl, OCProvisionResultCB resultCallback,
            OCStackResult expectedResult);
    bool getCredResource(void* ctx, const OCProvisionDev_t *selectedDeviceInfo,
            OCProvisionResultCB resultCallback, OCStackResult expectedResult);
    bool getACLResource(void* ctx, const OCProvisionDev_t *selectedDeviceInfo,
            OCProvisionResultCB resultCallback, OCStackResult expectedResult);
    bool unlinkDevices(void* ctx, const OCProvisionDev_t* pTargetDev1,
            const OCProvisionDev_t* pTargetDev2, OCProvisionResultCB resultCallback,
            OCStackResult expectedResult);
    bool removeDevice(void* ctx, unsigned short waitTimeForOwnedDeviceDiscovery,
            const OCProvisionDev_t* pTargetDev, OCProvisionResultCB resultCallback,
            OCStackResult expectedResult);
    bool getLinkedStatus(const OicUuid_t* uuidOfDevice, OCUuidList_t** uuidList,
            size_t* numOfDevices, OCStackResult expectedResult);

    /**
     * All Callback Methods for Provision Manager
     */
    static void ownershipTransferCB(void* ctx, int nOfRes, OCProvisionResult_t* arr, bool hasError);
    static void provisionPairwiseCB(void* ctx, int nOfRes, OCProvisionResult_t* arr, bool hasError);
    static void provisionCredCB(void* ctx, int nOfRes, OCProvisionResult_t* arr, bool hasError);
    static void provisionAclCB(void* ctx, int nOfRes, OCProvisionResult_t* arr, bool hasError);
    static void getAclCB(void* ctx, int nOfRes, OCProvisionResult_t* arr, bool hasError);
    static void getCredCB(void* ctx, int nOfRes, OCProvisionResult_t* arr, bool hasError);
    static void unlinkDevicesCB(void* ctx, int nOfRes, OCProvisionResult_t* arr, bool hasError);
    static void removeDeviceCB(void* ctx, int nOfRes, OCProvisionResult_t* arr, bool hasError);

    static ByteArray getTrustCertChainArray();
    bool provisionTrustCertChain(void *ctx, OicSecCredType_t type, uint16_t credId,
            const OCProvisionDev_t *selectedDeviceInfo, OCProvisionResultCB resultCallback,
            OCStackResult expectedResult);
    bool saveTrustCertChain(uint8_t *trustCertChain, size_t chainSize,
            OicEncodingType_t encodingType, uint16_t *credId, OCStackResult expectedResult);
    /**
     * All Utility Methods for Provision Manager
     */
    std::string getFailureMessage();
};
#endif