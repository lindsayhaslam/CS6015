.PHONY: all clean


# Define the executables
EXECUTABLES = msdscript0 msdscript1 msdscript2 msdscript3 msdscript4 msdscript5 msdscript6 msdscript7

all:
	@for exec in $(EXECUTABLES); do \
		echo "Processing $$exec"; \
		chmod a+x $$exec; \
		xattr -d com.apple.quarantine $$exec || true; \
	done

clean:
	@echo "Cleaning up..."
	# Add cleanup commands if necessary


clean:
	@echo "Cleaning up..."
	@# Add clean up commands here if necessary




