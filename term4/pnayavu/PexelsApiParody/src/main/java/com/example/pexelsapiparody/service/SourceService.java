package com.example.pexelsapiparody.service;

import com.example.pexelsapiparody.dto.SourceDto;
import com.example.pexelsapiparody.model.Source;

import java.util.List;

public interface SourceService {
    List<SourceDto> getAllSources();

    void createSource(Source source);

    SourceDto updateSource(Long id, Source source);

    void deleteSource(Long id);

}
