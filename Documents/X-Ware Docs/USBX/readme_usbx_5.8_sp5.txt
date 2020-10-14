Revision History


USBX generic code version 5.8 Service Pack 5 (SP5).  To install SP5, simply copy files in SP5 into the same
directory of your USBX 5.8 distribution and then rebuild the USBX library as well as the application code.

11/01/2018  USBX Service Pack code version 5.8 SP5 This release includes the following  modifications:

            ux_api.h                                        Added remote wakeup, and storage sync cache support,
                                                            added pending thread in transfer control structure.

            ux_dcd_rx.h                                     Added define guard for UX_RX_USB_BASE.

            ux_dcd_sim_slave.h                              Added prototype for transfer abort.
            ux_dcd_sim_slave_function.c                     Added support for transfer abort.
            ux_dcd_sim_slave_transfer_abort.c               Added support for transfer abort.

            ux_hcd_sim_host_transaction_schedule.c          Improved STALL handling, and thread wakeup flow.

            ux_device_stack_alternate_setting_get.c         Returned error code instead of stall on protocol error.
            ux_device_stack_alternate_setting_set.c         Added device state check, improved resource management
                                                            on error cases, improved error protocol report in case
                                                            no setting found, returned error code instead of stall
                                                            on protocol error.
            ux_device_stack_clear_feature.c                 Added device remote wakeup support.
            ux_device_stack_configuration_set.c             Improved configuration search and selecting flow, added
                                                            power state and remote wakeup support.
            ux_device_stack_control_request_process.c       Returned protocol error on SetDescriptor request, added
                                                            DCD call to send STALL (protocol error) when request
                                                            handling function return error.
            ux_device_stack_get_status.c                    Added device remote wakeup support.
            ux_device_stack_host_wakeup.c                   Call DCD to send remote wakeup only it's enabled.
            ux_device_stack_interface_set.c                 Improved resource management on error cases.
            ux_device_stack_interface_start.c               Fixed issue in case class driver not registered.
            ux_device_stack_set_feature.c                   Added device remote wakeup support.

            ux_host_stack_device_resources_free.c           Added filter to clean device resources.
            ux_host_stack_new_device_create.c               Improved error case handling and resources cleaning, changed
                                                            semaphore names.
            ux_host_stack_new_interface_create.c            Improved endpoint descriptor search method.
            ux_host_stack_rh_device_insertion.c             Improved device resources management in fail retry case.
            ux_host_stack_transfer_request.c                Fixed a possible race condition between this thread and enum
                                                            thread, saved pending thread in transfer request structure.
            ux_host_stack_transfer_request_abort.c          Added filter to put semaphore.

            ux_system.h                                     Added define guard UX_SOURCE_CODE for APIs.
            ux_system_initialize.c                          Added cache safe memory pool size initialization.
            ux_system_uninitialize.c                        Removed symbol UX_SYSTEM_INIT.
            ux_utility_memory_free.c                        Fixed regular memory range check issue.

            ux_device_class_cdc_acm.h                       Added parameter change callback, switched RTS to small data
                                                            type and added non-blocking read/write support.
            ux_device_class_cdc_acm_control_request.c       Added parameter(line coding and line state) change callback.
            ux_device_class_cdc_acm_deactivate.c            Added transmission stop for non-blocking read/write.
            ux_device_class_cdc_acm_initialize.c            Added parameter change callback.
            ux_device_class_cdc_acm_ioctl.c                 Added new IOCTLs, for LineState and non-blocking read/write.
            ux_device_class_cdc_acm_read.c                  Added protection when using non-blocking mode.
            ux_device_class_cdc_acm_write.c                 Added protection when using non-blocking mode.
            ux_device_class_cdc_acm_bulkin_thread.c         Thread for non-blocking write.
            ux_device_class_cdc_acm_bulkout_thread.c        Thread for non-blocking read.
            ux_device_class_cdc_acm_write_with_callback.c   Write to host with non-blocking callback mode.

            ux_device_class_storage.h                       Added write-protect support. Added uninitialize support.
                                                            Added strings (vendor id, product id, revision and serial)
                                                            customization by initialize parameter. Added SYNCHRONIZE
                                                            CACHE support.
            ux_device_class_storage_entry.c                 Added uninitialize support.
            ux_device_class_storage_initialize.c            Added write-protect support. Added strings customization.
                                                            Added SYNCHRONIZE CACHE support.
            ux_device_class_storage_inquiry.c               Used customized strings.
            ux_device_class_storage_mode_sense.c            Added write-protect support.
            ux_device_class_storage_thread.c                Added SYNCHRONIZE CACHE support.
            ux_device_class_storage_write.c                 Added write-protect support.
            ux_device_class_storage_synchronize_cache.c     Added SYNCHRONIZE CACHE support.
            ux_device_class_storage_uninitialize.c          Added uninitialize support.

            ux_host_class_cdc_acm_capabilities_get.c        Fixed resources free on error cases.
            ux_host_class_cdc_acm_reception_callback.c      Fixed reception overflow issue.

            ux_host_class_cdc_ecm_mac_address_get.c         Fixed length of mac address descriptor.

            ux_host_class_hid_keyboard.h                    Added keyboard layout support. Added IOCTL for layout and
                                                            decode setting.
            ux_host_class_hid_keyboard_activate.c           Added keyboard layout support.
            ux_host_class_hid_keyboard_callback.c           Fixed SHIFT and CAPS_LOCK decode issue. Added keyboard
                                                            layout support.
            ux_host_class_hid_keyboard_ioctl.c              Added IOCTL functions, for keyboard layout and decode.


Copyright(c) 1996-2018 Express Logic, Inc.


Express Logic, Inc.
11423 West Bernardo Court
San Diego, CA  92127

www.expresslogic.com

