#undef TRACE_SYSTEM
#define TRACE_SYSTEM f2fs

#if !defined(LTTNG_TRACE_F2FS_H) || defined(TRACE_HEADER_MULTI_READ)
#define LTTNG_TRACE_F2FS_H

#include <probes/lttng-tracepoint-event.h>
#include <linux/tracepoint.h>
#include <linux/writeback.h>

#ifndef _TRACE_F2FS_H
#define _TRACE_F2FS_H
struct victim_sel_policy;
struct f2fs_map_blocks;
#endif

LTTNG_TRACEPOINT_EVENT_CLASS(f2fs__inode,
    TP_PROTO(struct inode *inode),
    TP_ARGS(inode),
    TP_FIELDS(
        ctf_integer(dev_t, dev, inode->i_sb->s_dev)
        ctf_integer(ino_t, ino, inode->i_ino)
        ctf_integer(ino_t, pino, F2FS_I(inode)->i_pino)
        ctf_integer(umode_t, mode, inode->i_mode)
        ctf_integer(loff_t, size, inode->i_size)
        ctf_integer(unsigned int, nlink, inode->i_nlink)
        ctf_integer(blkcnt_t, blocks, inode->i_blocks)
        ctf_integer(__u8, advise, F2FS_I(inode)->i_advise)
    )
)

LTTNG_TRACEPOINT_EVENT_CLASS(f2fs__inode_exit,
    TP_PROTO(struct inode *inode, int ret),
    TP_ARGS(inode, ret),
    TP_FIELDS(
        ctf_integer(dev_t, dev, inode->i_sb->s_dev)
        ctf_integer(ino_t, ino, inode->i_ino)
        ctf_integer(int, ret, ret)
    )
)

LTTNG_TRACEPOINT_EVENT_INSTANCE(f2fs__inode, f2fs_sync_file_enter,
    TP_PROTO(struct inode *inode),
    TP_ARGS(inode)
)

LTTNG_TRACEPOINT_EVENT(f2fs_sync_file_exit,
    TP_PROTO(struct inode *inode, int need_cp, int datasync, int ret),
    TP_ARGS(inode, need_cp, datasync, ret),
    TP_FIELDS(
        ctf_integer(dev_t, dev, inode->i_sb->s_dev)
        ctf_integer(ino_t, ino, inode->i_ino)
        ctf_integer(int, need_cp, need_cp)
        ctf_integer(int, datasync, datasync)
        ctf_integer(int, ret, ret)
    )
)

LTTNG_TRACEPOINT_EVENT(f2fs_sync_fs,
    TP_PROTO(struct super_block *sb, int wait),
    TP_ARGS(sb, wait),
    TP_FIELDS(
        ctf_integer(dev_t, dev, sb->s_dev)
        ctf_integer(int, dirty, is_sbi_flag_set(F2FS_SB(sb), SBI_IS_DIRTY))
        ctf_integer(int, wait, wait)
    )
)

LTTNG_TRACEPOINT_EVENT_INSTANCE(f2fs__inode, f2fs_iget,
    TP_PROTO(struct inode *inode),
    TP_ARGS(inode)
)

LTTNG_TRACEPOINT_EVENT_INSTANCE(f2fs__inode_exit, f2fs_iget_exit,
    TP_PROTO(struct inode *inode, int ret),
    TP_ARGS(inode, ret)
)

LTTNG_TRACEPOINT_EVENT_INSTANCE(f2fs__inode, f2fs_evict_inode,
    TP_PROTO(struct inode *inode),
    TP_ARGS(inode)
)

LTTNG_TRACEPOINT_EVENT_INSTANCE(f2fs__inode_exit, f2fs_new_inode,
    TP_PROTO(struct inode *inode, int ret),
    TP_ARGS(inode, ret)
)

LTTNG_TRACEPOINT_EVENT(f2fs_unlink_enter,
    TP_PROTO(struct inode *dir, struct dentry *dentry),
    TP_ARGS(dir, dentry),
    TP_FIELDS(
        ctf_integer(dev_t, dev, dir->i_sb->s_dev)
        ctf_integer(ino_t, ino, dir->i_ino)
        ctf_integer(loff_t, size, dir->i_size)
        ctf_integer(blkcnt_t, blocks, dir->i_blocks)
        ctf_string(name, dentry->d_name.name)
    )
)

LTTNG_TRACEPOINT_EVENT_INSTANCE(f2fs__inode_exit, f2fs_unlink_exit,
    TP_PROTO(struct inode *inode, int ret),
    TP_ARGS(inode, ret)
)

LTTNG_TRACEPOINT_EVENT_INSTANCE(f2fs__inode_exit, f2fs_drop_inode,
    TP_PROTO(struct inode *inode, int ret),
    TP_ARGS(inode, ret)
)

LTTNG_TRACEPOINT_EVENT_INSTANCE(f2fs__inode, f2fs_truncate,
    TP_PROTO(struct inode *inode),
    TP_ARGS(inode)
)

LTTNG_TRACEPOINT_EVENT(f2fs_truncate_data_blocks_range,
    TP_PROTO(struct inode *inode, nid_t nid, unsigned int ofs, int free),
    TP_ARGS(inode, nid,  ofs, free),
    TP_FIELDS(
        ctf_integer(dev_t, dev, inode->i_sb->s_dev)
        ctf_integer(ino_t, ino, inode->i_ino)
        ctf_integer(nid_t, nid, nid)
        ctf_integer(unsigned int, ofs, ofs)
        ctf_integer(int, free, free)
    )
)

LTTNG_TRACEPOINT_EVENT_CLASS(f2fs__truncate_op,
    TP_PROTO(struct inode *inode, u64 from),
    TP_ARGS(inode, from),
    TP_FIELDS(
        ctf_integer(dev_t, dev, inode->i_sb->s_dev)
        ctf_integer(ino_t, ino, inode->i_ino)
        ctf_integer(loff_t, size, inode->i_size)
        ctf_integer(blkcnt_t, blocks, inode->i_blocks)
        ctf_integer(u64, from, from)
    )
)

LTTNG_TRACEPOINT_EVENT_INSTANCE(f2fs__truncate_op, f2fs_truncate_blocks_enter,
    TP_PROTO(struct inode *inode, u64 from),
    TP_ARGS(inode, from)
)

LTTNG_TRACEPOINT_EVENT_INSTANCE(f2fs__inode_exit, f2fs_truncate_blocks_exit,
    TP_PROTO(struct inode *inode, int ret),
    TP_ARGS(inode, ret)
)

LTTNG_TRACEPOINT_EVENT_INSTANCE(f2fs__truncate_op, f2fs_truncate_inode_blocks_enter,
    TP_PROTO(struct inode *inode, u64 from),
    TP_ARGS(inode, from)
)

LTTNG_TRACEPOINT_EVENT_INSTANCE(f2fs__inode_exit, f2fs_truncate_inode_blocks_exit,
    TP_PROTO(struct inode *inode, int ret),
    TP_ARGS(inode, ret)
)

LTTNG_TRACEPOINT_EVENT_CLASS(f2fs__truncate_node,
    TP_PROTO(struct inode *inode, nid_t nid, block_t blk_addr),
    TP_ARGS(inode, nid, blk_addr),
    TP_FIELDS(
        ctf_integer(dev_t, dev, inode->i_sb->s_dev)
        ctf_integer(ino_t, ino, inode->i_ino)
        ctf_integer(nid_t, nid, nid)
        ctf_integer(block_t, blk_addr, blk_addr)
    )
)

LTTNG_TRACEPOINT_EVENT_INSTANCE(f2fs__truncate_node, f2fs_truncate_nodes_enter,
    TP_PROTO(struct inode *inode, nid_t nid, block_t blk_addr),
    TP_ARGS(inode, nid, blk_addr)
)

LTTNG_TRACEPOINT_EVENT_INSTANCE(f2fs__inode_exit, f2fs_truncate_nodes_exit,
    TP_PROTO(struct inode *inode, int ret),
    TP_ARGS(inode, ret)
)

LTTNG_TRACEPOINT_EVENT_INSTANCE(f2fs__truncate_node, f2fs_truncate_node,
    TP_PROTO(struct inode *inode, nid_t nid, block_t blk_addr),
    TP_ARGS(inode, nid, blk_addr)
)

LTTNG_TRACEPOINT_EVENT(f2fs_truncate_partial_nodes,
    TP_PROTO(struct inode *inode, nid_t nid[], int depth, int err),
    TP_ARGS(inode, nid, depth, err),
    TP_FIELDS(
        ctf_integer(dev_t, dev, inode->i_sb->s_dev)
        ctf_integer(ino_t, ino, inode->i_ino)
        ctf_array(nid_t, nid, nid, 3)
        ctf_integer(int, depth, depth)
        ctf_integer(int, err, err)
    )
)

LTTNG_TRACEPOINT_EVENT(f2fs_map_blocks,
    TP_PROTO(struct inode *inode, struct f2fs_map_blocks *map, int ret),
    TP_ARGS(inode, map, ret),
    TP_FIELDS(
        ctf_integer(dev_t, dev, inode->i_sb->s_dev)
        ctf_integer(ino_t, ino, inode->i_ino)
        ctf_integer(block_t, m_lblk, map->m_lblk)
        ctf_integer(block_t, m_pblk, map->m_pblk)
        ctf_integer(unsigned int, m_len, map->m_len)
        ctf_integer(int, ret, ret)
    )
)

LTTNG_TRACEPOINT_EVENT(f2fs_background_gc,
    TP_PROTO(struct super_block *sb, unsigned int wait_ms,
        unsigned int prefree, unsigned int free),
    TP_ARGS(sb, wait_ms, prefree, free),
    TP_FIELDS(
        ctf_integer(dev_t, dev, sb->s_dev)
        ctf_integer(unsigned int, wait_ms, wait_ms)
        ctf_integer(unsigned int, prefree, prefree)
        ctf_integer(unsigned int, free, free)
    )
)

LTTNG_TRACEPOINT_EVENT(f2fs_gc_begin,
    TP_PROTO(struct super_block *sb, bool sync, bool background,
        long long dirty_nodes, long long dirty_dents,
        long long dirty_imeta, unsigned int free_sec,
        unsigned int free_seg, int reserved_seg,
        unsigned int prefree_seg),
    TP_ARGS(sb, sync, background, dirty_nodes, dirty_dents, dirty_imeta,
        free_sec, free_seg, reserved_seg, prefree_seg),
    TP_FIELDS(
        ctf_integer(dev_t, dev, sb->s_dev)
        ctf_integer(bool, sync, sync)
        ctf_integer(bool, background, background)
        ctf_integer(long long, dirty_nodes, dirty_nodes)
        ctf_integer(long long, dirty_dents, dirty_dents)
        ctf_integer(long long, dirty_imeta, dirty_imeta)
        ctf_integer(unsigned int, free_sec, free_sec)
        ctf_integer(unsigned int, free_seg, free_seg)
        ctf_integer(int, reserved_seg, reserved_seg)
        ctf_integer(unsigned int, prefree_seg, prefree_seg)
    )
)

LTTNG_TRACEPOINT_EVENT(f2fs_gc_end,
    TP_PROTO(struct super_block *sb, int ret, int seg_freed,
        int sec_freed, long long dirty_nodes,
        long long dirty_dents, long long dirty_imeta,
        unsigned int free_sec, unsigned int free_seg,
        int reserved_seg, unsigned int prefree_seg),
    TP_ARGS(sb, ret, seg_freed, sec_freed, dirty_nodes, dirty_dents,
        dirty_imeta, free_sec, free_seg, reserved_seg, prefree_seg),
    TP_FIELDS(
        ctf_integer(dev_t, dev, sb->s_dev)
        ctf_integer(int, ret, ret)
        ctf_integer(int, seg_freed, seg_freed)
        ctf_integer(int, sec_freed, sec_freed)
        ctf_integer(long long, dirty_nodes, dirty_nodes)
        ctf_integer(long long, dirty_dents, dirty_dents)
        ctf_integer(long long, dirty_imeta, dirty_imeta)
        ctf_integer(unsigned int, free_sec, free_sec)
        ctf_integer(unsigned int, free_seg, free_seg)
        ctf_integer(int, reserved_seg, reserved_seg)
        ctf_integer(unsigned int, prefree_seg, prefree_seg)
    )
)

LTTNG_TRACEPOINT_EVENT(f2fs_get_victim,
    TP_PROTO(struct super_block *sb, int type, int gc_type,
        struct victim_sel_policy *p, unsigned int pre_victim,
        unsigned int prefree, unsigned int free),
    TP_ARGS(sb, type, gc_type, p, pre_victim, prefree, free),
    TP_FIELDS(
        ctf_integer(dev_t, dev, sb->s_dev)
        ctf_integer(int, type, type)
        ctf_integer(int, gc_type, gc_type)
        ctf_integer(int, alloc_mode, p->alloc_mode)
        ctf_integer(int, gc_mode, p->gc_mode)
        ctf_integer(unsigned int, victim, p->min_segno)
        ctf_integer(unsigned int, cost, p->min_cost)
        ctf_integer(unsigned int, ofs_unit, p->ofs_unit)
        ctf_integer(unsigned int, pre_victim, pre_victim)
        ctf_integer(unsigned int, prefree, prefree)
        ctf_integer(unsigned int, free, free)
    )
)

LTTNG_TRACEPOINT_EVENT(f2fs_fallocate,
    TP_PROTO(struct inode *inode, int mode,
        loff_t offset, loff_t len, int ret),
    TP_ARGS(inode, mode, offset, len, ret),
    TP_FIELDS(
        ctf_integer(dev_t, dev, inode->i_sb->s_dev)
        ctf_integer(ino_t, ino, inode->i_ino)
        ctf_integer(int, mode, mode)
        ctf_integer(loff_t, offset, offset)
        ctf_integer(loff_t, len, len)
        ctf_integer(loff_t, size, inode->i_size)
        ctf_integer(blkcnt_t, blocks, inode->i_blocks)
        ctf_integer(int, ret, ret)
    )
)

LTTNG_TRACEPOINT_EVENT(f2fs_direct_IO_enter,
    TP_PROTO(struct inode *inode, loff_t offset, unsigned long len, int rw),
    TP_ARGS(inode, offset, len, rw),
    TP_FIELDS(
        ctf_integer(dev_t, dev, inode->i_sb->s_dev)
        ctf_integer(ino_t, ino, inode->i_ino)
        ctf_integer(loff_t, pos, offset)
        ctf_integer(unsigned long, len, len)
        ctf_integer(int, rw, rw)
    )
)

LTTNG_TRACEPOINT_EVENT(f2fs_direct_IO_exit,
    TP_PROTO(struct inode *inode, loff_t offset, unsigned long len,
        int rw, int ret),
    TP_ARGS(inode, offset, len, rw, ret),
    TP_FIELDS(
        ctf_integer(dev_t, dev, inode->i_sb->s_dev)
        ctf_integer(ino_t, ino, inode->i_ino)
        ctf_integer(loff_t, pos, offset)
        ctf_integer(unsigned long, len, len)
        ctf_integer(int, rw, rw)
        ctf_integer(int, ret, ret)
    )
)

LTTNG_TRACEPOINT_EVENT(f2fs_reserve_new_blocks,
    TP_PROTO(struct inode *inode, nid_t nid, unsigned int ofs_in_node,
        blkcnt_t count),
    TP_ARGS(inode, nid, ofs_in_node, count),
    TP_FIELDS(
        ctf_integer(dev_t, dev, inode->i_sb->s_dev)
        ctf_integer(nid_t, nid, nid)
        ctf_integer(unsigned int, ofs_in_node, ofs_in_node)
        ctf_integer(blkcnt_t, count, count)
    )
)

LTTNG_TRACEPOINT_EVENT_CLASS(f2fs__submit_page_bio,
    TP_PROTO(struct page *page, struct f2fs_io_info *fio),
    TP_ARGS(page, fio),
    TP_FIELDS(
        ctf_integer(dev_t, dev, page->mapping->host->i_sb->s_dev)
        ctf_integer(ino_t, ino, page->mapping->host->i_ino)
        ctf_integer(pgoff_t, index, page->index)
        ctf_integer(block_t, old_blkaddr, fio->old_blkaddr)
        ctf_integer(block_t, new_blkaddr, fio->new_blkaddr)
        ctf_integer(int, op, fio->op)
        ctf_integer(int, op_flags, fio->op_flags)
        ctf_integer(int, temp, fio->temp)
        ctf_integer(int, type, fio->type)
    )
)

// LTTNG_TRACEPOINT_EVENT_INSTANCE_CONDITION(f2fs__submit_page_bio, f2fs_submit_page_bio,
LTTNG_TRACEPOINT_EVENT_INSTANCE(f2fs__submit_page_bio, f2fs_submit_page_bio,
    TP_PROTO(struct page *page, struct f2fs_io_info *fio),
    TP_ARGS(page, fio)
    // TP_CONDITION(page->mapping)
)

//LTTNG_TRACEPOINT_EVENT_INSTANCE_CONDITION(f2fs__submit_page_bio, f2fs_submit_page_write,
LTTNG_TRACEPOINT_EVENT_INSTANCE(f2fs__submit_page_bio, f2fs_submit_page_write,
    TP_PROTO(struct page *page, struct f2fs_io_info *fio),
    TP_ARGS(page, fio)
    //TP_CONDITION(page->mapping)
)

LTTNG_TRACEPOINT_EVENT_CLASS(f2fs__bio,
    TP_PROTO(struct super_block *sb, int type, struct bio *bio),
    TP_ARGS(sb, type, bio),
    TP_FIELDS(
        ctf_integer(dev_t, dev, sb->s_dev)
        ctf_integer(dev_t, target, bio_dev(bio))
        ctf_integer(int, op, bio_op(bio))
        ctf_integer(int, op_flags, bio->bi_opf)
        ctf_integer(int, type, type)
        ctf_integer(sector_t, sector, bio->bi_iter.bi_sector)
        ctf_integer(unsigned int, size, bio->bi_iter.bi_size)
    )
)

//LTTNG_TRACEPOINT_EVENT_INSTANCE_CONDITION(f2fs__bio, f2fs_prepare_write_bio,
LTTNG_TRACEPOINT_EVENT_INSTANCE(f2fs__bio, f2fs_prepare_write_bio,
    TP_PROTO(struct super_block *sb, int type, struct bio *bio),
    TP_ARGS(sb, type, bio)
    //TP_CONDITION(bio)
)

//LTTNG_TRACEPOINT_EVENT_INSTANCE_CONDITION(f2fs__bio, f2fs_prepare_read_bio,
LTTNG_TRACEPOINT_EVENT_INSTANCE(f2fs__bio, f2fs_prepare_read_bio,
    TP_PROTO(struct super_block *sb, int type, struct bio *bio),
    TP_ARGS(sb, type, bio)
    //TP_CONDITION(bio)
)

//LTTNG_TRACEPOINT_EVENT_INSTANCE_CONDITION(f2fs__bio, f2fs_submit_read_bio,
LTTNG_TRACEPOINT_EVENT_INSTANCE(f2fs__bio, f2fs_submit_read_bio,
    TP_PROTO(struct super_block *sb, int type, struct bio *bio),
    TP_ARGS(sb, type, bio)
    //TP_CONDITION(bio)
)

//LTTNG_TRACEPOINT_EVENT_INSTANCE_CONDITION(f2fs__bio, f2fs_submit_write_bio,
LTTNG_TRACEPOINT_EVENT_INSTANCE(f2fs__bio, f2fs_submit_write_bio,
    TP_PROTO(struct super_block *sb, int type, struct bio *bio),
    TP_ARGS(sb, type, bio)
    //TP_CONDITION(bio)
)

LTTNG_TRACEPOINT_EVENT(f2fs_write_begin,
    TP_PROTO(struct inode *inode, loff_t pos, unsigned int len,
        unsigned int flags),
    TP_ARGS(inode, pos, len, flags),
    TP_FIELDS(
        ctf_integer(dev_t, dev, inode->i_sb->s_dev)
        ctf_integer(ino_t, ino, inode->i_ino)
        ctf_integer(loff_t, pos, pos)
        ctf_integer(unsigned int, len, len)
        ctf_integer(unsigned int, flags, flags)
    )
)

LTTNG_TRACEPOINT_EVENT(f2fs_write_end,
    TP_PROTO(struct inode *inode, loff_t pos, unsigned int len,
        unsigned int copied),
    TP_ARGS(inode, pos, len, copied),
    TP_FIELDS(
        ctf_integer(dev_t, dev, inode->i_sb->s_dev)
        ctf_integer(ino_t, ino, inode->i_ino)
        ctf_integer(loff_t, pos, pos)
        ctf_integer(unsigned int, len, len)
        ctf_integer(unsigned int, copied, copied)
    )
)

LTTNG_TRACEPOINT_EVENT(f2fs_file_write_iter_begin,
    TP_PROTO(struct inode *inode, loff_t pos, unsigned int len,
        unsigned int flags),
    TP_ARGS(inode, pos, len, flags),
    TP_FIELDS(
        ctf_integer(dev_t, dev, inode->i_sb->s_dev)
        ctf_integer(ino_t, ino, inode->i_ino)
        ctf_integer(loff_t, pos, pos)
        ctf_integer(unsigned int, len, len)
        ctf_integer(unsigned int, flags, flags)
    )
)

LTTNG_TRACEPOINT_EVENT(f2fs_file_write_iter_end,
    TP_PROTO(struct inode *inode, loff_t pos, unsigned int len,
        unsigned int copied),
    TP_ARGS(inode, pos, len, copied),
    TP_FIELDS(
        ctf_integer(dev_t, dev, inode->i_sb->s_dev)
        ctf_integer(ino_t, ino, inode->i_ino)
        ctf_integer(loff_t, pos, pos)
        ctf_integer(unsigned int, len, len)
        ctf_integer(unsigned int, copied, copied)
    )
)

LTTNG_TRACEPOINT_EVENT_CLASS(f2fs__page,
    TP_PROTO(struct page *page, int type),
    TP_ARGS(page, type),
    TP_FIELDS(
        ctf_integer(dev_t, dev, page->mapping->host->i_sb->s_dev)
        ctf_integer(ino_t, ino, page->mapping->host->i_ino)
        ctf_integer(int, type, type)
        ctf_integer(int, dir, S_ISDIR(page->mapping->host->i_mode))
        ctf_integer(pgoff_t, index, page->index)
        ctf_integer(int, dirty, PageDirty(page))
        ctf_integer(int, uptodate, PageUptodate(page))
    )
)

LTTNG_TRACEPOINT_EVENT_INSTANCE(f2fs__page, f2fs_writepage,
    TP_PROTO(struct page *page, int type),
    TP_ARGS(page, type)
)

LTTNG_TRACEPOINT_EVENT_INSTANCE(f2fs__page, f2fs_do_write_data_page,
    TP_PROTO(struct page *page, int type),
    TP_ARGS(page, type)
)

LTTNG_TRACEPOINT_EVENT_INSTANCE(f2fs__page, f2fs_readpage,
    TP_PROTO(struct page *page, int type),
    TP_ARGS(page, type)
)

LTTNG_TRACEPOINT_EVENT_INSTANCE(f2fs__page, f2fs_set_page_dirty,
    TP_PROTO(struct page *page, int type),
    TP_ARGS(page, type)
)

LTTNG_TRACEPOINT_EVENT_INSTANCE(f2fs__page, f2fs_vm_page_mkwrite,
    TP_PROTO(struct page *page, int type),
    TP_ARGS(page, type)
)

LTTNG_TRACEPOINT_EVENT_INSTANCE(f2fs__page, f2fs_register_inmem_page,
    TP_PROTO(struct page *page, int type),
    TP_ARGS(page, type)
)

LTTNG_TRACEPOINT_EVENT_INSTANCE(f2fs__page, f2fs_commit_inmem_page,
    TP_PROTO(struct page *page, int type),
    TP_ARGS(page, type)
)

LTTNG_TRACEPOINT_EVENT(f2fs_writepages,
    TP_PROTO(struct inode *inode, struct writeback_control *wbc, int type),
    TP_ARGS(inode, wbc, type),
    TP_FIELDS(
        ctf_integer(dev_t, dev, inode->i_sb->s_dev)
        ctf_integer(ino_t, ino, inode->i_ino)
        ctf_integer(int, type, type)
        ctf_integer(int, dir, S_ISDIR(inode->i_mode))
        ctf_integer(long, nr_to_write, wbc->nr_to_write)
        ctf_integer(long, pages_skipped, wbc->pages_skipped)
        ctf_integer(loff_t, range_start, wbc->range_start)
        ctf_integer(loff_t, range_end, wbc->range_end)
        ctf_integer(pgoff_t, writeback_index, inode->i_mapping->writeback_index)
        ctf_integer(int, sync_mode, wbc->sync_mode)
        ctf_integer(char, for_kupdate, wbc->for_kupdate)
        ctf_integer(char, for_background, wbc->for_background)
        ctf_integer(char, tagged_writepages, wbc->tagged_writepages)
        ctf_integer(char, for_reclaim, wbc->for_reclaim)
        ctf_integer(char, range_cyclic, wbc->range_cyclic)
        ctf_integer(char, for_sync, wbc->for_sync)
    )
)

LTTNG_TRACEPOINT_EVENT(f2fs_readpages,
    TP_PROTO(struct inode *inode, struct page *page, unsigned int nrpage),
    TP_ARGS(inode, page, nrpage),
    TP_FIELDS(
        ctf_integer(dev_t, dev, inode->i_sb->s_dev)
        ctf_integer(ino_t, ino, inode->i_ino)
        ctf_integer(pgoff_t, start, page->index)
        ctf_integer(unsigned int, nrpage, nrpage)
    )
)

LTTNG_TRACEPOINT_EVENT(f2fs_write_checkpoint,
    TP_PROTO(struct super_block *sb, int reason, char *msg),
    TP_ARGS(sb, reason, msg),
    TP_FIELDS(
        ctf_integer(dev_t, dev, sb->s_dev)
        ctf_integer(int, reason, reason)
        ctf_string(msg, msg)
    )
)

LTTNG_TRACEPOINT_EVENT_CLASS(f2fs_discard,
    TP_PROTO(struct block_device *dev, block_t blkstart, block_t blklen),
    TP_ARGS(dev, blkstart, blklen),
    TP_FIELDS(
        ctf_integer(dev_t, dev, dev->bd_dev)
        ctf_integer(block_t, blkstart, blkstart)
        ctf_integer(block_t, blklen, blklen)
    )
)

LTTNG_TRACEPOINT_EVENT_INSTANCE(f2fs_discard, f2fs_queue_discard,
    TP_PROTO(struct block_device *dev, block_t blkstart, block_t blklen),
    TP_ARGS(dev, blkstart, blklen)
)

LTTNG_TRACEPOINT_EVENT_INSTANCE(f2fs_discard, f2fs_issue_discard,
    TP_PROTO(struct block_device *dev, block_t blkstart, block_t blklen),
    TP_ARGS(dev, blkstart, blklen)
)

LTTNG_TRACEPOINT_EVENT(f2fs_issue_reset_zone,
    TP_PROTO(struct block_device *dev, block_t blkstart),
    TP_ARGS(dev, blkstart),
    TP_FIELDS(
        ctf_integer(dev_t, dev, dev->bd_dev)
        ctf_integer(block_t, blkstart, blkstart)
    )
)

LTTNG_TRACEPOINT_EVENT(f2fs_issue_flush,
    TP_PROTO(struct block_device *dev, unsigned int nobarrier,
        unsigned int flush_merge, int ret),
    TP_ARGS(dev, nobarrier, flush_merge, ret),
    TP_FIELDS(
        ctf_integer(dev_t, dev, dev->bd_dev)
        ctf_integer(unsigned int, nobarrier, nobarrier)
        ctf_integer(unsigned int, flush_merge, flush_merge)
        ctf_integer(int, ret, ret)
    )
)

LTTNG_TRACEPOINT_EVENT(f2fs_lookup_extent_tree_start,
    TP_PROTO(struct inode *inode, unsigned int pgofs),
    TP_ARGS(inode, pgofs),
    TP_FIELDS(
        ctf_integer(dev_t, dev, inode->i_sb->s_dev)
        ctf_integer(ino_t, ino, inode->i_ino)
        ctf_integer(unsigned int, pgofs, pgofs)
    )
)

//LTTNG_TRACEPOINT_EVENT_CONDITION(f2fs_lookup_extent_tree_end,
LTTNG_TRACEPOINT_EVENT(f2fs_lookup_extent_tree_end,
    TP_PROTO(struct inode *inode, unsigned int pgofs,
        struct extent_info *ei),
    TP_ARGS(inode, pgofs, ei),
    //TP_CONDITION(ei),
    TP_FIELDS(
        ctf_integer(dev_t, dev, inode->i_sb->s_dev)
        ctf_integer(ino_t, ino, inode->i_ino)
        ctf_integer(unsigned int, pgofs, pgofs)
        ctf_integer(unsigned int, fofs, ei->fofs)
        ctf_integer(u32, blk, ei->blk)
        ctf_integer(unsigned int, len, ei->len)
    )
)

LTTNG_TRACEPOINT_EVENT(f2fs_update_extent_tree_range,
    TP_PROTO(struct inode *inode, unsigned int pgofs, block_t blkaddr,
        unsigned int len),
    TP_ARGS(inode, pgofs, blkaddr, len),
    TP_FIELDS(
        ctf_integer(dev_t, dev, inode->i_sb->s_dev)
        ctf_integer(ino_t, ino, inode->i_ino)
        ctf_integer(unsigned int, pgofs, pgofs)
        ctf_integer(u32, blk, blkaddr)
        ctf_integer(unsigned int, len, len)
    )
)

LTTNG_TRACEPOINT_EVENT(f2fs_shrink_extent_tree,
    TP_PROTO(struct f2fs_sb_info *sbi, unsigned int node_cnt,
        unsigned int tree_cnt),
    TP_ARGS(sbi, node_cnt, tree_cnt),
    TP_FIELDS(
        ctf_integer(dev_t, dev, sbi->sb->s_dev)
        ctf_integer(unsigned int, node_cnt, node_cnt)
        ctf_integer(unsigned int, tree_cnt, tree_cnt)
    )
)

LTTNG_TRACEPOINT_EVENT(f2fs_destroy_extent_tree,
    TP_PROTO(struct inode *inode, unsigned int node_cnt),
    TP_ARGS(inode, node_cnt),
    TP_FIELDS(
        ctf_integer(dev_t, dev, inode->i_sb->s_dev)
        ctf_integer(ino_t, ino, inode->i_ino)
        ctf_integer(unsigned int, node_cnt, node_cnt)
    )
)

LTTNG_TRACEPOINT_EVENT_CLASS(f2fs_sync_dirty_inodes,
    TP_PROTO(struct super_block *sb, int type, s64 count),
    TP_ARGS(sb, type, count),
    TP_FIELDS(
        ctf_integer(dev_t, dev, sb->s_dev)
        ctf_integer(int, type, type)
        ctf_integer(s64, count, count)
    )
)

LTTNG_TRACEPOINT_EVENT_INSTANCE(f2fs_sync_dirty_inodes, f2fs_sync_dirty_inodes_enter,
    TP_PROTO(struct super_block *sb, int type, s64 count),
    TP_ARGS(sb, type, count)
)

LTTNG_TRACEPOINT_EVENT_INSTANCE(f2fs_sync_dirty_inodes, f2fs_sync_dirty_inodes_exit,
    TP_PROTO(struct super_block *sb, int type, s64 count),
    TP_ARGS(sb, type, count)
)

#endif //!defined(LTTNG_TRACE_F2FS_H) || defined(TRACE_HEADER_MULTI_READ)

/* This part must be outside protection */
#include <probes/define_trace.h>
