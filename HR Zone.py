def analyze_run(distance_km, time_str, avg_hr, max_hr=195, resting_hr=60):
    mins, secs = map(int, time_str.split(':'))
    total_seconds = mins * 60 + secs
    
    # 페이스 계산
    pace_sec_per_km = total_seconds / distance_km
    pace_min = int(pace_sec_per_km // 60)
    pace_sec = int(pace_sec_per_km % 60)
    
    # 여유 심박수(HRR) 기반 강도(%) 계산
    hrr = max_hr - resting_hr
    intensity = ((avg_hr - resting_hr) / hrr) * 100
    
    if intensity >= 90:
        zone = "Zone 5 (무산소성/최대 스피드)"
    elif intensity >= 80:
        zone = "Zone 4 (젖산 역치/템포런)"
    elif intensity >= 70:
        zone = "Zone 3 (유산소 지구력)"
    else:
        zone = "Zone 2 (지방 연소/회복 조깅)"
        
    print(f"거리: {distance_km}km | 기록: {time_str}")
    print(f"평균 페이스: {pace_min}'{pace_sec:02d}\"/km")
    print(f"평균 심박수: {avg_hr} bpm (운동 강도: {intensity:.1f}% -> {zone})")

analyze_run(5.0, "21:45", 174)
