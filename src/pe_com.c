/*

print_pe - Copyright 2005-2015 by Michael Kohn

Webpage: http://www.mikekohn.net/
Email: mike@mikekohn.net

This code falls under the LGPL license.

*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "fileio.h"
#include "pe_clsid.h"
#include "pe_com.h"

int read_reg_info(FILE *in, struct reg_info_t *reg_info, int offset)
{
  int marker;

  marker = ftell(in);
  fseek(in, offset, SEEK_SET);

  reg_info->bNextObject = read_uint32(in);
  reg_info->bObjectName = read_uint32(in);
  reg_info->bObjectDescription = read_uint32(in);
  reg_info->dwInstancing = read_uint32(in);
  reg_info->dwObjectId = read_uint32(in);
  read_clsid(in,(char *)reg_info->uuidObject);
  reg_info->fIsInterface = read_uint32(in);
  reg_info->bUidObjectIFace = read_uint32(in);
  reg_info->bUidEventsIFace = read_uint32(in);
  reg_info->fHasEvents = read_uint32(in);
  reg_info->dwMiscStatus = read_uint32(in);
  reg_info->fClassType = read_uint32(in);
  reg_info->fObjectType = read_uint16(in);
  reg_info->wToolboxBitmap32 = read_uint16(in);
  reg_info->wDefaultIcon = read_uint16(in);
  reg_info->fIsDesigner = read_uint16(in);
  reg_info->bDesignerData = read_uint32(in);

  fseek(in, marker, SEEK_SET);

  return 0;
}

int print_reg_info(struct reg_info_t *reg_info)
{
  printf("  -- COM Reg Info --\n");
  printf("       bNextObject: %d\n", reg_info->bNextObject);
  printf("       bObjectName: %d (%s)\n", reg_info->bObjectName,reg_info->szObjectName);
  printf("bObjectDescription: %d\n", reg_info->bObjectDescription);
  printf("      dwInstancing: %d\n", reg_info->dwInstancing);
  printf("        dwObjectId: %d\n", reg_info->dwObjectId);
  printf("        uuidObject: ");
  print_clsid(reg_info->uuidObject);
  printf("\n");
  printf("      fIsInterface: %d\n", reg_info->fIsInterface);
  printf("   bUidObjectIFace: %d\n", reg_info->bUidObjectIFace);
  printf("   bUidEventsIFace: %d\n", reg_info->bUidEventsIFace);
  printf("        fHasEvents: %d\n", reg_info->fHasEvents);
  printf("      dwMiscStatus: %d\n", reg_info->dwMiscStatus);
  printf("        fClassType: %d\n", reg_info->fClassType);
  printf("       fObjectType: %d\n", reg_info->fObjectType);
  printf("  wToolboxBitmap32: %d\n", reg_info->wToolboxBitmap32);
  printf("      wDefaultIcon: %d\n", reg_info->wDefaultIcon);
  printf("       fIsDesigner: %d\n", reg_info->fIsDesigner);
  printf("     bDesignerData: %d\n", reg_info->bDesignerData);
  printf("\n");

  return 0;
}

int read_com_reg_data(FILE *in, struct com_reg_data_t *com_reg_data, int offset)
{
  int marker;

  marker = ftell(in);
  fseek(in, offset, SEEK_SET);

  com_reg_data->bRegInfo = read_uint32(in);
  com_reg_data->bSZProjectName = read_uint32(in);
  com_reg_data->bSZHelpDirectory = read_uint32(in);
  com_reg_data->bSZProjectDescription = read_uint32(in);
  read_clsid(in,(char *)com_reg_data->uuidProjectClsId);
  com_reg_data->dwTlbLcid = read_uint32(in);
  com_reg_data->wUnknown = read_uint16(in);
  com_reg_data->wTlbVerMajor = read_uint16(in);
  com_reg_data->wTlbVerMinor = read_uint16(in);

  fseek(in, marker, SEEK_SET);

  return 0;
}

int print_com_reg_data(struct com_reg_data_t *com_reg_data)
{
  printf("  -- COM Reg Data --\n");
  printf("          bRegInfo: %d\n", com_reg_data->bRegInfo);
  printf("    bSZProjectName: %d\n", com_reg_data->bSZProjectName);
  printf("  bSZHelpDirectory: %d\n", com_reg_data->bSZHelpDirectory);
  printf("bSZProjectDescrptn: %d\n", com_reg_data->bSZProjectDescription);
  printf("  uuidProjectClsId: ");
  print_clsid(com_reg_data->uuidProjectClsId);
  printf("\n");
  printf("         dwTlbLcid: %d\n", com_reg_data->dwTlbLcid);
  printf("          wUnknown: %d\n", com_reg_data->wUnknown);
  printf("      wTlbVerMajor: %d\n", com_reg_data->wTlbVerMajor);
  printf("      wTlbVerMinor: %d\n", com_reg_data->wTlbVerMinor);
  printf("\n");

  return 0;
}

