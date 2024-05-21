package com.example.pexelsapiparody.mapper;

import com.example.pexelsapiparody.dto.SourceDto;
import com.example.pexelsapiparody.model.Source;
import org.springframework.stereotype.Component;

import java.util.ArrayList;
import java.util.List;

@Component
public class SourceMapper {

    public static SourceDto toDto(Source model) {
        return new SourceDto(
                model.getId(),
                model.getOriginal(),
                model.getMedium()
        );
    }

    public static Source toModel(SourceDto dto) {
        return new Source(
                dto.getId(),
                dto.getOriginal(),
                dto.getMedium()
        );
    }

    public static List<SourceDto> toDtos(List<Source> models) {
        List<SourceDto> dtos = new ArrayList<>();
        if (models != null) {
            for (Source model : models) {
                dtos.add(toDto(model));
            }
        }
        return dtos;
    }

    public static List<Source> toModels(List<SourceDto> dtos) {
        List<Source> models = new ArrayList<>();
        if (dtos != null) {
            for (SourceDto dto : dtos) {
                models.add(toModel(dto));
            }
        }
        return models;
    }

}
