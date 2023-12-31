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

include(${CMAKE_CURRENT_LIST_DIR}/../../cmake/function/hypervisor_add_integration_target.cmake)

hypervisor_add_integration_target(bf_callback_op_register_bootstrap)
hypervisor_add_integration_target(bf_callback_op_register_fail)
hypervisor_add_integration_target(bf_callback_op_register_vmexit)
hypervisor_add_integration_target(bf_debug_op_dump_ext)
hypervisor_add_integration_target(bf_debug_op_dump_huge_pool)
hypervisor_add_integration_target(bf_debug_op_dump_page_pool)
hypervisor_add_integration_target(bf_debug_op_dump_vm)
hypervisor_add_integration_target(bf_debug_op_dump_vmexit_log)
hypervisor_add_integration_target(bf_debug_op_dump_vp)
hypervisor_add_integration_target(bf_debug_op_dump_vs)
hypervisor_add_integration_target(bf_debug_op_out)
hypervisor_add_integration_target(bf_debug_op_write_c)
hypervisor_add_integration_target(bf_debug_op_write_str)
hypervisor_add_integration_target(bf_handle_op_close_handle)
hypervisor_add_integration_target(bf_handle_op_open_handle)
hypervisor_add_integration_target(bf_intrinsic_op_rdmsr)
hypervisor_add_integration_target(bf_intrinsic_op_wrmsr)
hypervisor_add_integration_target(bf_mem_op_alloc_huge)
hypervisor_add_integration_target(bf_mem_op_alloc_page)
hypervisor_add_integration_target(bf_vm_op_create_vm)
hypervisor_add_integration_target(bf_vm_op_destroy_vm)
hypervisor_add_integration_target(bf_vm_op_map_direct)
hypervisor_add_integration_target(bf_vm_op_tlb_flush)
hypervisor_add_integration_target(bf_vm_op_unmap_direct)
hypervisor_add_integration_target(bf_vp_op_create_vp)
hypervisor_add_integration_target(bf_vp_op_destroy_vp)
hypervisor_add_integration_target(bf_vs_op_create_vs)
hypervisor_add_integration_target(bf_vs_op_destroy_vs)
hypervisor_add_integration_target(bf_vs_op_advance_ip_and_run_current)
hypervisor_add_integration_target(bf_vs_op_advance_ip_and_run)
hypervisor_add_integration_target(bf_vs_op_advance_ip_and_set_active)
hypervisor_add_integration_target(bf_vs_op_clear)
hypervisor_add_integration_target(bf_vs_op_init_as_root)
hypervisor_add_integration_target(bf_vs_op_migrate)
hypervisor_add_integration_target(bf_vs_op_promote)
hypervisor_add_integration_target(bf_vs_op_read)
hypervisor_add_integration_target(bf_vs_op_run_current)
hypervisor_add_integration_target(bf_vs_op_run)
hypervisor_add_integration_target(bf_vs_op_set_active)
hypervisor_add_integration_target(bf_vs_op_tlb_flush)
hypervisor_add_integration_target(bf_vs_op_write)
hypervisor_add_integration_target(fast_fail_exit_from_bootstrap_with_no_syscall)
hypervisor_add_integration_target(fast_fail_exit_from_bootstrap_with_segfault)
hypervisor_add_integration_target(fast_fail_exit_from_bootstrap_with_wait)
hypervisor_add_integration_target(fast_fail_exit_from_bootstrap)
hypervisor_add_integration_target(fast_fail_exit_from_fail_with_no_syscall)
hypervisor_add_integration_target(fast_fail_exit_from_fail_with_segfault)
hypervisor_add_integration_target(fast_fail_exit_from_fail_with_wait)
hypervisor_add_integration_target(fast_fail_exit_from_fail)
hypervisor_add_integration_target(fast_fail_exit_from_main_with_no_syscall)
hypervisor_add_integration_target(fast_fail_exit_from_main_with_segfault)
hypervisor_add_integration_target(fast_fail_exit_from_main)
hypervisor_add_integration_target(fast_fail_exit_from_vmexit_with_no_syscall)
hypervisor_add_integration_target(fast_fail_exit_from_vmexit_with_segfault)
hypervisor_add_integration_target(fast_fail_exit_from_vmexit_with_wait)
hypervisor_add_integration_target(fast_fail_exit_from_vmexit)
hypervisor_add_integration_target(fast_fail_from_fail_handler)
hypervisor_add_integration_target(fast_fail_recover_from_assert)
hypervisor_add_integration_target(fast_fail_recover_from_page_fault)
hypervisor_add_integration_target(fast_fail_wait_no_bootstrap)
hypervisor_add_integration_target(fast_fail_wait_no_fail)
hypervisor_add_integration_target(fast_fail_wait_no_vmexit)
