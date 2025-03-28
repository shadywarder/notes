**2025-03-23 16:51**
**Tags:** [dbms](../2%20-%20tags/dbms.md)

## Transactions Isolation Practice

### Write-Skew #1. Serializable

Scheme:

```sql
drop table if exists doctors;
create table doctors (
	id serial primary key,
	username varchar(255) not null unique,
	on_call numeric not null
)
insert into doctors (username, on_call) values ('alice', 1), ('bob', 1);
```

Transaction 1:

```sql
begin;
set transaction level serializable;
show transaction isolation level;

select * from doctors where on_call = 1;

update doctors set on_call = 0 
where username = 'alice' returning *;

commit;
```

Transaction 2:

```sql
begin;
set transaction level serializable;
show transaction isolation level;

select * from doctors where on_call = 1;

update doctors set on_call = 0 
where username = 'bob' returning *;

commit;
```

## References
[Изоляции транзакций практика](https://www.youtube.com/watch?v=iWLH6PinQbI)