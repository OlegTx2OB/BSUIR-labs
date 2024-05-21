package com.example.pexelsapiparody.dto;

import lombok.AllArgsConstructor;
import lombok.Getter;
import lombok.NoArgsConstructor;
import lombok.Setter;

import java.util.ArrayList;
import java.util.List;

@Getter
@Setter
@AllArgsConstructor
@NoArgsConstructor
public class CollectionDto {
    private long id;
    private String name;
    private List<PhotoDto> photoDtos = new ArrayList<>();
}
