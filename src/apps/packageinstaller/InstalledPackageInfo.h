/*
 * Copyright (c) 2007, Haiku, Inc.
 * Distributed under the terms of the MIT license.
 *
 * Author:
 *		Łukasz 'Sil2100' Zemczak <sil2100@vexillium.org>
 */
#ifndef INSTALLED_PACKAGE_INFO_H
#define INSTALLED_PACKAGE_INFO_H

#include <File.h>
#include <String.h>
#include <List.h>
#include <Path.h>


#define P_BUSY_TRIES 10

enum {
	P_PACKAGE_INFO = 'ppki'
};

extern const char * kPackagesDir;


// Useful function for fetching the package name and version without parsing all
// other data
status_t info_get_package_name(const char* filename, BString& name);
status_t info_get_package_version(const char* filename, BString& name);


class InstalledPackageInfo {
public:
								InstalledPackageInfo();
								InstalledPackageInfo(const char* packageName,
									const char* version = NULL, 
									bool create = false);
								~InstalledPackageInfo();

			status_t			InitCheck();
			status_t			SetTo(const char* packageName,
									const char* version = NULL, 
									bool create = false);

			void				SetName(const char* name)
									{ fName = name; }
			const char*			Name()
									{ return fName.String(); }
			void				SetDescription(const char* description)
									{ fDescription = description; }
			const char*			Description()
									{ return fDescription.String(); }
			const char*			Version()
									{ return fVersion.String(); }
			void				SetSpaceNeeded(uint64 size)
									{ fSpaceNeeded = size; }
			uint64				SpaceNeeded()
									{ return fSpaceNeeded; }

			status_t			AddItem(const char* itemName);

			status_t			Uninstall();
			status_t			Save();

private:
			void				_ClearItemList();

private:
			status_t			fStatus;
			bool				fIsUpToDate;
			bool				fCreate;

			BString				fName;
			BString				fDescription;
			BString				fVersion;
			uint64				fSpaceNeeded;
			BList				fInstalledItems;

			BPath				fPathToInfo;
};


#endif // INSTALLED_PACKAGE_INFO_H

