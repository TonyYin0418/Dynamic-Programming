// a[i].x=id,a[i].y=cnt[i]-rem[p[i]],a[i].tp=(p[i]>0);
void cdq(int l, int r)
{
    if(l >= r) return;
    int mid = (l + r) >> 1;
    cdq(l, mid);
    sort(a + l, a + mid + 1, cmpy);
    sort(a + mid + 1, a + r + 1, cmpy);
    int i = l, j = mid + 1;
    for(; j <= r; j++)
    {
        if(!a[j].tp) continue;
        while(i <= mid && a[i].y <= a[j].y)
        {
            if(a[i].tp) upd(a[i].p, a[i].f - rem[a[i].p]);
            i++;
        }
        a[j].f = max(a[j].f, qry(a[j].p) + rem[a[j].p] + 1);
    }
    for(j = l; j < i; j++)
        if(a[j].tp) clr(a[j].p);
    i = mid;
    j = r;
    for(; j > mid; j--)
    {
        while(i >= l && a[i].y > a[j].y)
        {
            if(a[i].tp) upd(a[i].p, a[i].f - cnt[a[i].p]);
            i++;
        }
        a[j].f = max(a[j].f, qry(a[j].p) + cnt[a[j].p] + 1);
    }
    for(j = mid; j > i; j--)
        if(a[j].tp) clr(a[j].p);
    sort(a + l, a + r + 1, cmpx);
    cdq(mid + 1, r);
}