

* src aligned and dest i have to check if aligned */
void *Memcpy(void *dest, const void *src, size_t num_of_bytes) 
{
	size_t index_address , steps_for_aligned;
	const char *ptr_runner = (char *)src;
	char *ptr_dest = (char *)dest;
	size_t *ptrx ,*ptry;
	
	index_address = (size_t)dest; /* where dest is pointing */
	
	if(num_of_bytes < WORD_SIZE)
	{
			/* mimosh byte byte */
		while(ptr_runner && num_of_bytes--)
		{
			*ptr_dest=*ptr_runner;
			ptr_runner++;	
		}
		return dest;
	}
	else
	{
		/* check if aligned */
		if(0 !=(index_address % WORD_SIZE))
		{
			steps_for_aligned = WORD_SIZE - (index_address % WORD_SIZE);
			ptr_runner += steps_for_aligned;
		}
		
		ptrx = (size_t *)src;
		ptry= (size_t *)dest;
		
		while(ptrx != NULL)
		{
			*ptry  =  *ptrx;	
			
			ptrx++;
		}
		return dest;
	}
}
