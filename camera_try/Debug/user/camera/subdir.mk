################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
"../user/camera/Atime.c" \
"../user/camera/barrier.c" \
"../user/camera/circle.c" \
"../user/camera/common.c" \
"../user/camera/cross.c" \
"../user/camera/date.c" \
"../user/camera/garage.c" \
"../user/camera/get_corners.c" \
"../user/camera/handle_img.c" \
"../user/camera/img_process.c" \
"../user/camera/state.c" \
"../user/camera/tracking.c" \
"../user/camera/transform_table.c" 

COMPILED_SRCS += \
"user/camera/Atime.src" \
"user/camera/barrier.src" \
"user/camera/circle.src" \
"user/camera/common.src" \
"user/camera/cross.src" \
"user/camera/date.src" \
"user/camera/garage.src" \
"user/camera/get_corners.src" \
"user/camera/handle_img.src" \
"user/camera/img_process.src" \
"user/camera/state.src" \
"user/camera/tracking.src" \
"user/camera/transform_table.src" 

C_DEPS += \
"./user/camera/Atime.d" \
"./user/camera/barrier.d" \
"./user/camera/circle.d" \
"./user/camera/common.d" \
"./user/camera/cross.d" \
"./user/camera/date.d" \
"./user/camera/garage.d" \
"./user/camera/get_corners.d" \
"./user/camera/handle_img.d" \
"./user/camera/img_process.d" \
"./user/camera/state.d" \
"./user/camera/tracking.d" \
"./user/camera/transform_table.d" 

OBJS += \
"user/camera/Atime.o" \
"user/camera/barrier.o" \
"user/camera/circle.o" \
"user/camera/common.o" \
"user/camera/cross.o" \
"user/camera/date.o" \
"user/camera/garage.o" \
"user/camera/get_corners.o" \
"user/camera/handle_img.o" \
"user/camera/img_process.o" \
"user/camera/state.o" \
"user/camera/tracking.o" \
"user/camera/transform_table.o" 


# Each subdirectory must supply rules for building sources it contributes
"user/camera/Atime.src":"../user/camera/Atime.c" "user/camera/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2004 -D__CPU__=tc26xb "-fG:/Very_NB/camera_try/Debug/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -Y0 -N0 -Z0 -o "$@" "$<"
"user/camera/Atime.o":"user/camera/Atime.src" "user/camera/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
"user/camera/barrier.src":"../user/camera/barrier.c" "user/camera/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2004 -D__CPU__=tc26xb "-fG:/Very_NB/camera_try/Debug/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -Y0 -N0 -Z0 -o "$@" "$<"
"user/camera/barrier.o":"user/camera/barrier.src" "user/camera/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
"user/camera/circle.src":"../user/camera/circle.c" "user/camera/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2004 -D__CPU__=tc26xb "-fG:/Very_NB/camera_try/Debug/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -Y0 -N0 -Z0 -o "$@" "$<"
"user/camera/circle.o":"user/camera/circle.src" "user/camera/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
"user/camera/common.src":"../user/camera/common.c" "user/camera/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2004 -D__CPU__=tc26xb "-fG:/Very_NB/camera_try/Debug/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -Y0 -N0 -Z0 -o "$@" "$<"
"user/camera/common.o":"user/camera/common.src" "user/camera/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
"user/camera/cross.src":"../user/camera/cross.c" "user/camera/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2004 -D__CPU__=tc26xb "-fG:/Very_NB/camera_try/Debug/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -Y0 -N0 -Z0 -o "$@" "$<"
"user/camera/cross.o":"user/camera/cross.src" "user/camera/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
"user/camera/date.src":"../user/camera/date.c" "user/camera/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2004 -D__CPU__=tc26xb "-fG:/Very_NB/camera_try/Debug/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -Y0 -N0 -Z0 -o "$@" "$<"
"user/camera/date.o":"user/camera/date.src" "user/camera/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
"user/camera/garage.src":"../user/camera/garage.c" "user/camera/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2004 -D__CPU__=tc26xb "-fG:/Very_NB/camera_try/Debug/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -Y0 -N0 -Z0 -o "$@" "$<"
"user/camera/garage.o":"user/camera/garage.src" "user/camera/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
"user/camera/get_corners.src":"../user/camera/get_corners.c" "user/camera/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2004 -D__CPU__=tc26xb "-fG:/Very_NB/camera_try/Debug/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -Y0 -N0 -Z0 -o "$@" "$<"
"user/camera/get_corners.o":"user/camera/get_corners.src" "user/camera/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
"user/camera/handle_img.src":"../user/camera/handle_img.c" "user/camera/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2004 -D__CPU__=tc26xb "-fG:/Very_NB/camera_try/Debug/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -Y0 -N0 -Z0 -o "$@" "$<"
"user/camera/handle_img.o":"user/camera/handle_img.src" "user/camera/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
"user/camera/img_process.src":"../user/camera/img_process.c" "user/camera/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2004 -D__CPU__=tc26xb "-fG:/Very_NB/camera_try/Debug/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -Y0 -N0 -Z0 -o "$@" "$<"
"user/camera/img_process.o":"user/camera/img_process.src" "user/camera/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
"user/camera/state.src":"../user/camera/state.c" "user/camera/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2004 -D__CPU__=tc26xb "-fG:/Very_NB/camera_try/Debug/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -Y0 -N0 -Z0 -o "$@" "$<"
"user/camera/state.o":"user/camera/state.src" "user/camera/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
"user/camera/tracking.src":"../user/camera/tracking.c" "user/camera/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2004 -D__CPU__=tc26xb "-fG:/Very_NB/camera_try/Debug/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -Y0 -N0 -Z0 -o "$@" "$<"
"user/camera/tracking.o":"user/camera/tracking.src" "user/camera/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
"user/camera/transform_table.src":"../user/camera/transform_table.c" "user/camera/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2004 -D__CPU__=tc26xb "-fG:/Very_NB/camera_try/Debug/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -Y0 -N0 -Z0 -o "$@" "$<"
"user/camera/transform_table.o":"user/camera/transform_table.src" "user/camera/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"

clean: clean-user-2f-camera

clean-user-2f-camera:
	-$(RM) ./user/camera/Atime.d ./user/camera/Atime.o ./user/camera/Atime.src ./user/camera/barrier.d ./user/camera/barrier.o ./user/camera/barrier.src ./user/camera/circle.d ./user/camera/circle.o ./user/camera/circle.src ./user/camera/common.d ./user/camera/common.o ./user/camera/common.src ./user/camera/cross.d ./user/camera/cross.o ./user/camera/cross.src ./user/camera/date.d ./user/camera/date.o ./user/camera/date.src ./user/camera/garage.d ./user/camera/garage.o ./user/camera/garage.src ./user/camera/get_corners.d ./user/camera/get_corners.o ./user/camera/get_corners.src ./user/camera/handle_img.d ./user/camera/handle_img.o ./user/camera/handle_img.src ./user/camera/img_process.d ./user/camera/img_process.o ./user/camera/img_process.src ./user/camera/state.d ./user/camera/state.o ./user/camera/state.src ./user/camera/tracking.d ./user/camera/tracking.o ./user/camera/tracking.src ./user/camera/transform_table.d ./user/camera/transform_table.o ./user/camera/transform_table.src

.PHONY: clean-user-2f-camera

