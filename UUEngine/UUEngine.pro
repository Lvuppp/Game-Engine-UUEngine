TEMPLATE = subdirs

SUBDIRS += \
    EngineUI \
    EngineCore \
    EngineEntities \

EngineCore.subdir = EngineCore
EngineEntities.subdir = EngineEntities

EngineUI.depends = EngineCore EngineEntities
