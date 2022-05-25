#ifndef _SCATTERLIST_H
#define _SCATTERLIST_H

struct scatterlist {
	unsigned long	page_link;
	unsigned int	offset;
	unsigned int	length;
	dma_addr_t	dma_address;
#ifdef CONFIG_NEED_SG_DMA_LENGTH
	unsigned int	dma_length;
#endif
};

struct sg_table {
	struct scatterlist *sgl;	/* the list */
	unsigned int nents;		/* number of mapped entries */
	unsigned int orig_nents;	/* original size of list */
};


#endif /* _SCATTERLIST_H */
