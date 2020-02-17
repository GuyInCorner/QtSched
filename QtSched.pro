TEMPLATE = subdirs

SUBDIRS += Source
SUBDIRS += Test

CONFIG += ordered

Test.depends = Source
