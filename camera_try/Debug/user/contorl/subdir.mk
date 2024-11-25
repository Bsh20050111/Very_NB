################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
"../user/contorl/Kalman.c" \
"../user/contorl/Smart_Init.c" \
"../user/contorl/Smart_ips.c" \
"../user/contorl/Smart_key.c" \
"../user/contorl/Smart_motor.c" 

COMPILED_SRCS += \
"user/contorl/Kalman.src" \
"user/contorl/Smart_Init.src" \
"user/contorl/Smart_ips.src" \
"user/contorl/Smart_key.src" \
"user/contorl/Smart_motor.src" 

C_DEPS += \
"./user/contorl/Kalman.d" \
"./user/contorl/Smart_Init.d" \
"./user/contorl/Smart_ips.d" \
"./user/contorl/Smart_key.d" \
"./user/contorl/Smart_motor.d" 

OBJS += \
"user/contorl/Kalman.o" \
"user/contorl/Smart_Init.o" \
"user/contorl/Smart_ips.o" \
"user/contorl/Smart_key.o" \
"user/contorl/Smart_motor.o" 


# Each subdirectory must supply rules for building sources it contributes
"user/contorl/Kalman.src":"../user/contorl/Kalman.c" "user/contorl/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2004 -D__CPU__=tc26xb "-fG:/Very_NB/camera_try/Debug/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -Y0 -N0 -Z0 -o "$@" "$<"
"user/contorl/Kalman.o":"user/contorl/Kalman.src" "user/contorl/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
"user/contorl/Smart_Init.src":"../user/contorl/Smart_Init.c" "user/contorl/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2004 -D__CPU__=tc26xb "-fG:/Very_NB/camera_try/Debug/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -Y0 -N0 -Z0 -o "$@" "$<"
"user/contorl/Smart_Init.o":"user/contorl/Smart_Init.src" "user/contorl/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
"user/contorl/Smart_ips.src":"../user/contorl/Smart_ips.c" "user/contorl/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2004 -D__CPU__=tc26xb "-fG:/Very_NB/camera_try/Debug/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -Y0 -N0 -Z0 -o "$@" "$<"
"user/contorl/Smart_ips.o":"user/contorl/Smart_ips.src" "user/contorl/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
"user/contorl/Smart_key.src":"../user/contorl/Smart_key.c" "user/contorl/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2004 -D__CPU__=tc26xb "-fG:/Very_NB/camera_try/Debug/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -Y0 -N0 -Z0 -o "$@" "$<"
"user/contorl/Smart_key.o":"user/contorl/Smart_key.src" "user/contorl/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
"user/contorl/Smart_motor.src":"../user/contorl/Smart_motor.c" "user/contorl/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2004 -D__CPU__=tc26xb "-fG:/Very_NB/camera_try/Debug/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -Y0 -N0 -Z0 -o "$@" "$<"
"user/contorl/Smart_motor.o":"user/contorl/Smart_motor.src" "user/contorl/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"

clean: clean-user-2f-contorl

clean-user-2f-contorl:
	-$(RM) ./user/contorl/Kalman.d ./user/contorl/Kalman.o ./user/contorl/Kalman.src ./user/contorl/Smart_Init.d ./user/contorl/Smart_Init.o ./user/contorl/Smart_Init.src ./user/contorl/Smart_ips.d ./user/contorl/Smart_ips.o ./user/contorl/Smart_ips.src ./user/contorl/Smart_key.d ./user/contorl/Smart_key.o ./user/contorl/Smart_key.src ./user/contorl/Smart_motor.d ./user/contorl/Smart_motor.o ./user/contorl/Smart_motor.src

.PHONY: clean-user-2f-contorl

