package com.example.pexelsapiparody.mapper;

import com.example.pexelsapiparody.dto.PhotoDto;
import com.example.pexelsapiparody.model.Photo;
import org.springframework.stereotype.Component;

import java.util.ArrayList;
import java.util.List;

@Component
public class PhotoMapper {

    public static PhotoDto toDto(Photo model) {
        return new PhotoDto(
                model.getId(),
                model.getPhotographer(),
                SourceMapper.toDto(model.getSource())
        );
    }

    public static Photo toModel(PhotoDto dto) {
        return new Photo(
                dto.getId(),
                dto.getPhotographer(),
                SourceMapper.toModel(dto.getSourceDto())
        );
    }

    public static List<PhotoDto> toDtos(List<Photo> models) {
        List<PhotoDto> dtos = new ArrayList<>();
        if (models != null) {
            for (Photo model : models) {
                dtos.add(toDto(model));
            }
        }
        return dtos;
    }

    public static List<Photo> toModels(List<PhotoDto> dtos) {
        List<Photo> models = new ArrayList<>();
        if (dtos != null) {
            for (PhotoDto dto : dtos) {
                models.add(toModel(dto));
            }
        }
        return models;
    }
}
