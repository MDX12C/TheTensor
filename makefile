clean:
	mv ./log/log_00.txt ./log/tmp
	rm -vf ./log/log_*
	mv ./log/tmp ./log/log_00.txt
