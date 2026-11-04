# cuddle

Epitech project (G-AIA-200). A small dataframe library written in C, inspired by pandas.

## Build

```
make
```

This produces the static library `libcuddle.a`. The public API is in `include/dataframe.h`.

## Features

- Read and write CSV files: `df_read_csv`, `df_write_csv`
- Inspect a dataframe: `df_shape`, `df_head`, `df_tail`, `df_info`, `df_describe`
- Read values: `df_get_value`, `df_get_values`, `df_get_unique_values`
- Transform data: `df_to_type`, `df_filter`, `df_apply`, `df_sort`, `df_groupby`
- Free memory: `df_free`

## Layout

- `src/pandas`: one file per dataframe function
- `src/utils`: type handling, data structures, conversions
- `src/lib`: string and list helpers
