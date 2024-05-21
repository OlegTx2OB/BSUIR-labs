package com.example.pexelsapiparody.mapper;

import com.example.pexelsapiparody.dto.CollectionDto;
import com.example.pexelsapiparody.model.Collection;
import org.springframework.stereotype.Component;

import java.util.ArrayList;
import java.util.List;

@Component
public class CollectionMapper {

    public static CollectionDto toDto(Collection collection) {
        return new CollectionDto(
                collection.getId(),
                collection.getName(),
                PhotoMapper.toDtos(collection.getPhotos())
        );
    }

    public static Collection toModel(CollectionDto collectionDto) {
        return new Collection(
                collectionDto.getId(),
                collectionDto.getName(),
                PhotoMapper.toModels(collectionDto.getPhotoDtos())
        );
    }

    public static List<CollectionDto> toDtos(List<Collection> models) {
        List<CollectionDto> dtos = new ArrayList<>();
        if (models != null) {
            for (Collection model : models) {
                dtos.add(toDto(model));
            }
        }
        return dtos;
    }

    public static List<Collection> toModels(List<CollectionDto> dtos) {
        List<Collection> models = new ArrayList<>();
        if (dtos != null) {
            for (CollectionDto dto : dtos) {
                models.add(toModel(dto));
            }
        }
        return models;
    }
}
