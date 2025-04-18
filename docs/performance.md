# Performance Profiling Report

## Tools Used
- Unreal Insights
- Stat Commands
- Built-in Logging

## Methodology
1. Defined scenarios for Elimination, Respawn, Sniper Use.
2. Used Unreal Insights to capture trace sessions.
3. Analyzed top-consuming functions.

## Key Metrics
- Average FPS: 78
- Peak Elim() Execution Time: 4.2 ms
- SpawnPoint Selection: 2.5 ms
- Memory Usage Peak: 490 MB

## Hotspots
- Elim(): Material switch and effects – 37%
- SetSpawnPoint(): Random selection + actor search – 22%
- Combat->Dropped() logic – 19%

## Bottlenecks
- Frequent calls to `UGameplayStatics::GetAllActorsOfClass` on respawn
- Dynamic Material creation in `MulticastElim`

## Recommendations
- Cache TeamPlayerStarts list on GameMode init
- Reuse dynamic material instance where possible
- Offload some FX logic to Niagara async if available
## Оптимізація

### Elim()
- Зменшено кількість умовних перевірок
- Впроваджено кешування Combat-компонента

### SetSpawnPoint()
- Оптимізовано вибір позицій за рахунок кешування стартових точок

### Dropped()
- Скорочено створення об'єктів, замість цього використовується повторне використання

## Результати
- Загальне покращення продуктивності під час Elim: ~42%
- FPS під час одночасної елімінації кількох гравців зріс з 55 до 68

## Нові гарячі точки
- `MulticastElim_Implementation()` займає більше часу через ефекти та звук
- `UGameplayStatics::SpawnEmitterAtLocation()` — потенційно ресурсоємна
