package com.example.pexelsapiparody.service.impl;

import com.example.pexelsapiparody.dto.SourceDto;
import com.example.pexelsapiparody.mapper.SourceMapper;
import com.example.pexelsapiparody.model.Source;
import com.example.pexelsapiparody.repository.SourceRepository;
import com.example.pexelsapiparody.service.SourceService;
import lombok.Getter;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.List;

@Getter
@Service
public class SourceServiceImpl implements SourceService {
    private final SourceRepository mSourceRepository;

    @Autowired
    public SourceServiceImpl(SourceRepository mSourceRepository) {
        this.mSourceRepository = mSourceRepository;
    }

    @Override
    public List<SourceDto> getAllSources() {
        return SourceMapper.toDtos(mSourceRepository.findAll());
    }

    @Override
    public void createSource(Source source) {
        mSourceRepository.save(source);
    }

    @Override
    public SourceDto updateSource(Long id, Source source) {
        source.setId(id);
        return SourceMapper.toDto(mSourceRepository.save(source));
    }

    @Override
    public void deleteSource(Long id) {
        mSourceRepository.deleteById(id);
    }
}
