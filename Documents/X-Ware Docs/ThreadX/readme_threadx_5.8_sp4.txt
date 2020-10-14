Revision History

10-10-2018  ThreadX generic code version 5.8 Service Pack 4 (SP4). To install SP4, simply 
            copy the files in SP4 into the same directory of your ThreadX 5.8 distribution
            and then rebuild the ThreadX library as well as the application code. Please note
            that SP4 contains all prior service packs as well.
            
            SP4 includes the following modifications:
            
                        File                                    Changes
                        
                tx_api.h                            Added a macro to disable warning of 
                                                    parameter not used, and added a symbol for 
                                                    identifying service pack release number.
                tx_event_flags_set.c                Moved setup of notify callback so that it 
                                                    is under interrupt protection and before any 
                                                    preemption.
                tx_event_flags_set_notify.c         Removed the warning of parameter not used.
                tx_mutex_get.c                      Changed logic to update the priority inheritance
                                                    priority level.
                tx_mutex_priority_change.c          Removed update of the priority inheritance
                                                    priority level.
                tx_mutex_put.c                      Changed logic to properly update the priority 
                                                    inheritance priority level.
                tx_queue_send_notify.c              Removed the warning of parameter not used.
                tx_semaphore_put_notify.c           Removed the warning of parameter not used.
                tx_thread_entry_exit_notify.c       Removed the warning of parameter not used.
                tx_thread_suspend.c                 Refined error checking for self suspension to 
                                                    ensure thread context. Modifed to use system
                                                    state macro instead of direct variable access.

