CURRENT_DIR := $(shell pwd)
GITCONFIG_PATH := $(CURRENT_DIR)/.gitconfig

gitconfig-status:
	git config --list

gitconfig-apply: $(GITCONFIG_PATH)
	git config --global include.path $(GITCONFIG_PATH)

gitconfig-unapply:
	git config --global --unset include.path

gitconfig-reset: unapply apply status