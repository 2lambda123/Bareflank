#
# Copyright (C) 2020 Assured Information Security, Inc.
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

# NOTE:
# - We include the bf_add_test function from the BSL as it greatly simplifies
#   creating unit tests for us. If you do not want to use this, feel free to
#   handle unit tests however you wish (or not at all)
#

include(${bsl_SOURCE_DIR}/cmake/function/bf_add_test.cmake)

# ------------------------------------------------------------------------------
# Includes
# ------------------------------------------------------------------------------

# NOTE:
# - It is really, really important that we do not add any include directories
#   from the source folder. Anything that is needed by code from the source
#   folder must be mocked. The include folder itself is fine as this should
#   only ever include type definitions. Things that should not be in the
#   include folder are:
#   - Any code that can excute. Anything that can execute must be in the src
#     folder and have a set of tests associated with it.
#   - C function prototypes. These should also be in the source folder, and
#     any code that needs them should get to this code through a C++ class
#     wrapper. See the intrinsic_t as an example. C function prototypes are not
#     constexpr, so they cannot be called from the rest of the C++ code.
#   - Obiviously, any actual source files like .cpp and .S. These should all
#     be in the source folder as well. Unit test the assembly files where it
#     is possible (like a memcpy/memset). For extensions, most assembly files
#     likely can be unit tested as they can only execute userspace specific
#     instructions. The microkernel is a different story as it executes system
#     instructions which likely need an emulator to properly unit test.
# - In the default example, we include the mock folder for bf_syscall_t and
#   it's related headers. This is a generic mock of bf_syscall_t which can be
#   used for most unit testing, but if you need soemthing more specific, you
#   are free to remove the includes for this and provide your own. The sycall
#   library stores bf_syscall_t in the source folder for this reason as the
#   include folder contains type defintions and constants that can be used in
#   any unit test as they do not change, while the src folder specific logic
#   should only be included when you plan to use the actual implementation of
#   bf_syscall_t and not a mock.
#

list(APPEND COMMON_INCLUDES
    ${CMAKE_CURRENT_LIST_DIR}/../include
    ${CMAKE_CURRENT_LIST_DIR}/../mocks
)

list(APPEND COMMON_SYSTEM_INCLUDES
    ${CMAKE_SOURCE_DIR}/syscall/include
    ${CMAKE_SOURCE_DIR}/syscall/mocks
    ${CMAKE_SOURCE_DIR}/lib/include
    ${CMAKE_SOURCE_DIR}/lib/mocks
    ${CMAKE_SOURCE_DIR}/loader/include/interface
)

list(APPEND X64_INCLUDES
    ${CMAKE_CURRENT_LIST_DIR}/../include/x64
    ${CMAKE_CURRENT_LIST_DIR}/../mocks/x64
    ${COMMON_INCLUDES}
)

list(APPEND X64_SYSTEM_INCLUDES
    ${CMAKE_SOURCE_DIR}/syscall/include/x64
    ${CMAKE_SOURCE_DIR}/syscall/mocks/x64
    ${CMAKE_SOURCE_DIR}/lib/include/x64
    ${CMAKE_SOURCE_DIR}/lib/mocks/x64
    ${CMAKE_SOURCE_DIR}/loader/include/interface/x64
    ${COMMON_SYSTEM_INCLUDES}
)

list(APPEND AMD_INCLUDES
    ${CMAKE_CURRENT_LIST_DIR}/../include/x64/amd
    ${CMAKE_CURRENT_LIST_DIR}/../mocks/x64/amd
    ${X64_INCLUDES}
)

list(APPEND AMD_SYSTEM_INCLUDES
    ${CMAKE_SOURCE_DIR}/syscall/include/x64/amd
    ${CMAKE_SOURCE_DIR}/syscall/mocks/x64/amd
    ${CMAKE_SOURCE_DIR}/lib/include/x64/amd
    ${CMAKE_SOURCE_DIR}/lib/mocks/x64/amd
    ${CMAKE_SOURCE_DIR}/loader/include/interface/x64/amd
    ${X64_SYSTEM_INCLUDES}
)

list(APPEND INTEL_INCLUDES
    ${CMAKE_CURRENT_LIST_DIR}/../include/x64/intel
    ${CMAKE_CURRENT_LIST_DIR}/../mocks/x64/intel
    ${X64_INCLUDES}
)

list(APPEND INTEL_SYSTEM_INCLUDES
    ${CMAKE_SOURCE_DIR}/syscall/include/x64/intel
    ${CMAKE_SOURCE_DIR}/syscall/mocks/x64/intel
    ${CMAKE_SOURCE_DIR}/lib/include/x64/intel
    ${CMAKE_SOURCE_DIR}/lib/mocks/x64/intel
    ${CMAKE_SOURCE_DIR}/loader/include/interface/x64/intel
    ${X64_SYSTEM_INCLUDES}
)

# ------------------------------------------------------------------------------
# Definitions
# ------------------------------------------------------------------------------

# NOTE:
# - Any defintions that the extension uses should be defined here. You can
#   also define them on a per unit test basis if needed. Bareflank makes the
#   definitions available to the extension when it is compiling the actual
#   code, but it does not make them available to any tests, so they must be
#   manually defined here, or where you define the unit test itself.
# - DO NOT define these in the unit test code. Either define them here, or
#   to define them on a per unit test bases, add them to a test specific
#   CMake variable that is passed to bf_add_test. If a unit test needs these
#   defined different for each test, make a different unit test for each one.
#
# - See the individual CMakeLists.txt for each test for more information.
#

list(APPEND DEFINES
    HYPERVISOR_PAGE_SIZE=0x1000_umx
    HYPERVISOR_MAX_PPS=2_umx
    HYPERVISOR_MAX_VMS=2_umx
    HYPERVISOR_MAX_VPS=2_umx
    HYPERVISOR_MAX_VSS=2_umx
    HYPERVISOR_EXT_DIRECT_MAP_ADDR=0x0000600000000000_umx
    HYPERVISOR_EXT_DIRECT_MAP_SIZE=0x0000200000000000_umx
)

list(APPEND COMMON_DEFINES
    ${DEFINES}
)

list(APPEND X64_DEFINES
    ${DEFINES}
)

list(APPEND AMD_DEFINES
    ${X64_DEFINES}
)

list(APPEND INTEL_DEFINES
    ${X64_DEFINES}
)

list(APPEND AARCH64_DEFINES
    ${DEFINES}
)

# ------------------------------------------------------------------------------
# Tests
# ------------------------------------------------------------------------------

# NOTE:
# - The following is just a template that you can use as a starting point for
#   each test. Remove it from your extension as needed.
#

add_subdirectory(template)

# NOTE:
# - Add the directories for each unit test here. Note that you should add all
#   archiectures here. Unit tests mock all dependencies, including the arch
#   specific dependencies, so all of the arch specific unit tests can compile
#   and run on any other arch. This ensures, for example, that your ARM logic
#   is unit tested during CI which might be running on an Intel based system.
#

add_subdirectory(mocks/dispatch_bootstrap)
add_subdirectory(mocks/dispatch_fail)
add_subdirectory(mocks/dispatch_vmexit)
add_subdirectory(mocks/intrinsic_t)
add_subdirectory(mocks/gs_initialize)
add_subdirectory(mocks/tls_initialize)
add_subdirectory(mocks/vp_pool_t)
add_subdirectory(mocks/vp_t)
add_subdirectory(mocks/vs_pool_t)
add_subdirectory(mocks/vs_t)
add_subdirectory(mocks/x64/dispatch_vmexit_cpuid)
add_subdirectory(mocks/x64/intrinsic_cpuid_impl)
add_subdirectory(mocks/x64/intrinsic_t)
add_subdirectory(mocks/x64/intel/dispatch_vmexit_nmi_window)
add_subdirectory(mocks/x64/intel/dispatch_vmexit_nmi)

add_subdirectory(src/dispatch_bootstrap)
add_subdirectory(src/dispatch_fail)
add_subdirectory(src/main)
add_subdirectory(src/vp_pool_t)
add_subdirectory(src/vp_t)
add_subdirectory(src/vs_pool_t)
add_subdirectory(src/x64/dispatch_vmexit_cpuid)
add_subdirectory(src/x64/intrinsic_t)
add_subdirectory(src/x64/amd/dispatch_vmexit)
add_subdirectory(src/x64/amd/gs_initialize)
add_subdirectory(src/x64/amd/tls_initialize)
add_subdirectory(src/x64/amd/vs_t)
add_subdirectory(src/x64/intel/dispatch_vmexit_nmi_window)
add_subdirectory(src/x64/intel/dispatch_vmexit_nmi)
add_subdirectory(src/x64/intel/dispatch_vmexit)
add_subdirectory(src/x64/intel/gs_initialize)
add_subdirectory(src/x64/intel/tls_initialize)
add_subdirectory(src/x64/intel/vs_t)
