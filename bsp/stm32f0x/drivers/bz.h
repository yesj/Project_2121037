#ifndef __BZ_H__
#define __BZ_H__

extern struct rt_event bz_event;

#define bz_short3bz()			rt_event_send(&bz_event, 0x04);

#define bz_short()		rt_event_send(&bz_event, 0x02);

#define bz_long()			rt_event_send(&bz_event, 0x01);


#endif
