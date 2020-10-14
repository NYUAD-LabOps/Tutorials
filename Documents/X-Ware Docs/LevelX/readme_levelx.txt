                        Express Logic's LevelX  

1. Revision History

The LevelX generic code version information is as follows:

05/01/2018  LevelX generic code version 5.4. This release includes the following 
            modifications:

            lx_api.h                                        Added NOR flash RAM buffer, added bit constant
                                                            for both NOR and NAND flash to indicate when 
                                                            mapping write is valid, added diagnostic counter
                                                            for tracking when incomplete mapping is detected 
                                                            on open, add added new error code when driver 
                                                            does not supply a sector/page RAM buffer.
            fx_nand_flash_simulated_driver.c                Added error checking, and corrected sector 
                                                            read/write processing.
            fx_nor_flash_simulator_driver.c                 Added error checking.
            lx_nand_flash_block_reclaim.c                   Added clearing of additional bit to indicate when 
                                                            mapping is valid, and corrected logic that could 
                                                            cause a newly mapped sector to be erased.
            lx_nand_flash_logical_sector_find.c             Added logic to make sure the sector mapping is valid.
            lx_nand_flash_next_block_to_erase_find.c        Added logic to improve search for free sectors.
            lx_nand_flash_open.c                            Added logic to detect and handle a mapping entry 
                                                            interrupted before completion, and added logic to 
                                                            ensure there is a page buffer supplied by the 
                                                            driver.
            lx_nand_flash_sector_release.c                  Added reclaim logic to help increase free sectors.
            lx_nand_flash_sector_write.c                    Added clearing of additional bit to indicate when 
                                                            mapping is valid.
            lx_nor_flash_block_reclaim.c                    Added clearing of additional bit to indicate when 
                                                            mapping is valid, added logic to read NOR sector 
                                                            into RAM buffer if direct NOR access is not possible, 
                                                            and corrected logic that could cause a newly mapped 
                                                            sector to be erased.
            lx_nor_flash_logical_sector_find.c              Added logic to make sure the sector mapping is valid.
            lx_nor_flash_next_block_to_erase_find.c         Added logic to improve search for free sectors.
            lx_nor_flash_open.c                             Added logic to detect and handle a mapping entry 
                                                            interrupted before completion, and added logic to 
                                                            ensure there is a sector buffer supplied by the 
                                                            driver if LX_DIRECT_READ is not specified.          
            lx_nor_flash_sector_release.c                   Added reclaim logic to help increase free sectors.
            lx_nor_flash_sector_write.c                     Added clearing of additional bit to indicate when 
                                                            mapping is valid, and removed optimization to ensure
                                                            atomic sector write.
            lx_nor_flash_simulator.c                        Added logic to supply RAM buffer for reading
                                                            sector when LX_DIRECT_READ is not specified, 
                                                            and removed write attempt to already written
                                                            sector, since this is no longer required.
            fx*.c                                           Changed comments and copyright header.
            lx*.c                                           Changed comments and copyright header.
            lx*.h                                           Changed comments and copyright header.


11/01/2017  LevelX generic code version 5.3. This release includes the following 
            modifications:

            lx_nand_flash_block_full_update.c               Added check to make sure the block is 
                                                            actually full.
            lx_nand_flash_block_reclaim.c                   Added support for direct logical sector 
                                                            cache.
            lx_nand_flash_logical_sector_find.c             Added adjustment of mapped sectors when 
                                                            examining the mapped list, added support 
                                                            for direct logical sector cache.
            lx_nand_flash_open.c                            Added support for direct logical sector cache, 
                                                            and updated diagnostics.
            lx_nand_flash_physical_page_allocate.c          Added adjustment of the search pointer for 
                                                            next allocate request.
            lx_nand_flash_sector_mapping_cache_invalidate.c Added support for direct logical sector cache.
            lx_nand_flash_sector_release.c                  Added logic to update the page 0 mapping list 
                                                            if present.
            lx_nand_flash_sector_write.c                    Added logic to update the page 0 mapping list 
                                                            if present, and added check to make sure the 
                                                            new mapping wasn't moved, added direct logical 
                                                            sector cache.
            fx*.c                                           Changed comments and copyright header.
            lx*.c                                           Changed comments and copyright header.
            lx*.h                                           Changed comments and copyright header.

03/01/2017  LevelX generic code version 5.2. This release includes the following 
            modifications:

            lx_nand_flash_block_full_update.c               Reduced the number of words accessed in 
                                                            page 0, added driver interface layer,  
                                                            and modified the extra bytes usage in 
                                                            page 0 to support block valid-full-empty.
            lx_nand_flash_block_obsoleted_check.c           Added file in this release.
            lx_nand_flash_block_reclaim.c                   Added logic to update page 0 on a full 
                                                            block update, added driver interface layer, 
                                                            and added additional diagnostic information.
            lx_nand_flash_driver_block_erase.c              Added file in this release.
            lx_nand_flash_driver_block_erased_verify.c      Added file in this release.
            lx_nand_flash_driver_block_status_get.c         Added file in this release.
            lx_nand_flash_driver_block_status_set.c         Added file in this release.
            lx_nand_flash_driver_extra_bytes_get.c          Added file in this release.
            lx_nand_flash_driver_extra_bytes_set.c          Added file in this release.
            lx_nand_flash_driver_page_erased_verify.c       Added file in this release.
            lx_nand_flash_driver_read.c                     Added file in this release.
            lx_nand_flash_driver_write.c                    Added file in this release.
            lx_nand_flash_extended_cache_enable.c           Added file in this release.
            lx_nand_flash_logical_sector_find.c             Reduced the number of words accessed in 
                                                            page 0, corrected check for valid sector 
                                                            mapping list, added max mapped sector logic, 
                                                            added driver interface layer, and added logic 
                                                            to use and maintain the last found sector block.
            lx_nand_flash_next_block_to_erase_find.c        Reduced the number of words accessed in page 0, 
                                                            and added driver interface layer.
            lx_nand_flash_open.c                            Reduced the number of words accessed in page 0, 
                                                            added driver interface layer, added additional 
                                                            diagnostic information, added logic to initialize 
                                                            the maximum mapped logical sector, and added 
                                                            initialization of the last found sector block.
            lx_nand_flash_physical_page_allocate.c          Reduced the number of words accessed in page 0, 
                                                            added driver interface layer, and added logic 
                                                            to use page 0's extra bytes to determine if  
                                                            block has available pages.
            lx_nand_flash_sector_read.c                     Added driver interface layer.
            lx_nand_flash_sector_release.c                  Added logic to maintain the maximum mapped 
                                                            sector, and added driver interface layer.
            lx_nand_flash_sector_write.c                    Added call to see if the block is completely 
                                                            obsoleted, added logic to remember the maximum 
                                                            mapped sector, and added driver interface layer.
            fx_nand_flash_simulator_driver.c                Removed sector packing by requiring sector and 
                                                            cluster size to match, and added release sector 
                                                            support.
            fx*.c                                           Changed comments and copyright header.
            lx*.c                                           Changed comments and copyright header.
            lx*.h                                           Changed comments and copyright header.

08/01/2016  LevelX generic code version 5.1. This release includes the following 
            modifications:

            lx_nor_flash_physical_sector_allocate.c         Corrected problem with more than 32 sectors per 
                                                            flash block.
            fx*.c                                           Changed comments and copyright header.
            lx*.c                                           Changed comments and copyright header.
            lx*.h                                           Changed comments and copyright header.

01/22/2015  Initial LevelX generic code version 5.0. 


Copyright(c) 1996-2018 Express Logic, Inc.


Express Logic, Inc.
11423 West Bernardo Court
San Diego, CA  92127

www.expresslogic.com


