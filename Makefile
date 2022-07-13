#
# Top level makefile for omc_agent(SNMP agent) application
#
#
# Copyright (C) 2010-2014 6Harmonics Inc.
#
# 
#
include $(TOPDIR)/rules.mk
PKG_NAME:=omc_agent
PKG_VERSION:=1.20
PKG_RELEASE:=1

#PKG_BUILD_DIR := $(BUILD_DIR)/$(PKG_NAME)

include $(INCLUDE_DIR)/package.mk

define Package/omc_agent
  SECTION:=utils
  CATEGORY:=Utilities
  TITLE:=6H-GWS SNMP agent
  DEPENDS:=+libstdcpp +libgwsapi +libpthread
  MAINTAINER:=6Harmonics
endef

define Package/omc_agent/description
  6Harmonics GWS SNMP agent
endef


define Build/Prepare
	$(CP) -r ./include $(PKG_BUILD_DIR)/
	$(CP) -r ./src $(PKG_BUILD_DIR)/
	$(CP) -r ./libs $(PKG_BUILD_DIR)/
	$(CP) -r ./nbproject $(PKG_BUILD_DIR)/
	$(CP) ./mk/Makefile-nb $(PKG_BUILD_DIR)/Makefile
endef

define Build/Configure
endef
	
define Package/omc_agent/install
	$(INSTALL_DIR) $(1)/usr/sbin
	$(INSTALL_DIR) $(1)/etc/config
	$(INSTALL_DIR) $(1)/etc/init.d
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/dist/Release/GNU_GWS5000_4_4_14-Linux/omc_agent $(1)/usr/sbin/gwssnmpd
	#$(INSTALL_BIN) $(PKG_BUILD_DIR)/src/gwssnmpd $(1)/usr/sbin/gwssnmpd
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/src/omcagent.conf $(1)/etc/config/omcagent.conf
	$(INSTALL_CONF) $(PKG_BUILD_DIR)/src/gwssnmpd.conf $(1)/etc/config/gwssnmpd
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/src/gwssnmpd.init $(1)/etc/init.d/gwssnmpd
endef

$(eval $(call BuildPackage,omc_agent))
