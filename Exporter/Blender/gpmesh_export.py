

bl_info = {
    "name": "gpmesh Exporter",
    "blender": (3,00,0),
    "category": "Export"
}

import bpy
import json

def generate_gpmesh_json():
    mesh = bpy.context.active_object.data
    uv_layer = mesh.uv_layers.active.data

    gpmesh = {
        "version": 1,
        "vertexformat": "PosNormSkinTex",
        "shader": "Skinned",
        "textures": [],
        "specularPower": 100.0,
        "vertices": [],
        "indices": []
    }

    for vert in mesh.vertices:
        pos = vert.co
        normal = vert.normal
        uv = uv_layer[vert.index].uv
        gp_vert = []
        gp_vert.extend([pos.x, pos.y, pos.z])
        gp_vert.extend([normal.x, normal.y, normal.z])

        # get bone indices and their weights that affect this vertex and sort them by weight from high to low
        boneToWeightTuples = []
        for group in vert.groups:
            u8_weight = int(group.weight * 255)
            boneToWeightTuples.append((group.group, u8_weight))
        boneToWeightTuples.sort(key=lambda boneToWeight : boneToWeight[1], reverse=True)
        
        # Only keep first 4 bones with their weights. As we sorted them by their bone weight (from high to low)
        # before, we only keep the once with highest influence.
        boneToWeightTuples = boneToWeightTuples[:4]
        
        # The file format expects always 4 bones.
        while len(boneToWeightTuples) < 4:
            boneToWeightTuples.append((0, 0))
        
        boneIndices = []
        weights = []
        for boneIdx, weight in boneToWeightTuples:
            boneIndices.append(boneIdx)
            weights.append(weight)

        gp_vert.extend(boneIndices)
        gp_vert.extend(weights)
        gp_vert.extend([uv.x, uv.y])
        
        gpmesh["vertices"].append(gp_vert)
    
    for poly in mesh.polygons:
        tri = []
        for loop_index in poly.loop_indices:
            vertIndex = mesh.loops[loop_index].vertex_index
            tri.append(vertIndex)
        
        gpmesh["indices"].append(tri)
    
    textures = []
    materialSlots = bpy.context.active_object.material_slots
    for matSlot in materialSlots:
        if matSlot.material:
            if matSlot.material.node_tree:
                for node in matSlot.material.node_tree.nodes:
                    if node.type == 'TEX_IMAGE':
                        textures.append("Assets/" + node.image.name)

    gpmesh["textures"] = textures
    
    return gpmesh

def find_armature(active_object):
    armature = active_object
    while armature.parent and armature.type != 'ARMATURE':
        armature = armature.parent
    
    if armature.type == 'ARMATURE':
        return armature
    return None

def generate_gpskel_json():
    gpskel = {
        "version": 1,
        "bonecount": 0,
        "bones": []
    }
    boneInfos = []

    armature = find_armature(bpy.context.active_object)
    if armature:
        armature = armature.data
        for i, bone in enumerate(armature.bones):
            parentBone = bone.parent
            parentIndex = -1
            if parentBone:
                parentIndex = armature.bones.find(parentBone.name)
            
            local_matrix = bone.matrix_local
            trans = local_matrix.to_translation()
            rot = local_matrix.to_quaternion()
            boneInfo = {
                "name": bone.name,
                "index": i,
                "parent": parentIndex,
                "bindpose": {
                    "rot": [rot.x, rot.y, rot.z, rot.w],
                    "trans": [trans.x, trans.y, trans.z]
                }
            }
            boneInfos.append(boneInfo)
        
        gpskel["bonecount"] = len(armature.bones)

    gpskel["bones"] = boneInfos

    return gpskel

def generate_gpanim_json(action):
    gpanim = {
        "version": 1,
        "sequence": {
            "frames": 0,
            "length": 1.0, # TODO: Calculate from framerate
            "bonecount": 0,
            "tracks": []
        }
    }
    active_object = bpy.context.active_object
    # active_object.animation_data.action = action
    armature = find_armature(active_object)
    armature.animation_data.action = action
    frame_start, frame_end = int(action.frame_range.x), int(action.frame_range.y)
    gpanim["sequence"]["frames"] = frame_end - 1 # TODO: Hacky (engine expects duplicate of first keyframe at the end but should not count as one)
    gpanim["sequence"]["bonecount"] = len(armature.data.bones)
    for i, bone in enumerate(armature.pose.bones):
        track = {
            "bone": i,
            "transforms": []
        }
        for frame in range(frame_start, frame_end):
            bpy.context.scene.frame_set(frame)
            rot = bone.matrix.to_quaternion()
            trans = bone.matrix.to_translation()
            transform = {
                "rot": [rot.x, rot.y, rot.z, rot.w],
                "trans": [trans.x, trans.y, trans.z]
            }
            track["transforms"].append(transform)

        gpanim["sequence"]["tracks"].append(track)
    
    return gpanim

def write_to_disk(context, filepath, export_gpmesh, export_gpskel, export_gpanim):
    print("exporting to gpmesh...")

    if export_gpmesh:
        gpmesh = generate_gpmesh_json()
        f = open(filepath, 'w', encoding='utf-8')
        # f.write("Hello World %s" % use_some_setting)
        f.write(json.dumps(gpmesh, sort_keys=False, indent=2))
        f.close()
    
    if export_gpskel:
        gpskel = generate_gpskel_json()
        gpskel_filepath = filepath.split(".")[0] + '.gpskel'
        f = open(gpskel_filepath, "w", encoding="utf-8")
        f.write(json.dumps(gpskel, sort_keys=False, indent=2))
        f.close()
    
    if export_gpanim:
        print("EXPORT GPANIM")
        actions = bpy.data.actions
        print(actions)
        for action in actions:
            gpanim = generate_gpanim_json(action)
            gpanim_filepath = filepath.split(".")[0] + str(action.name) + '.gpanim'
            f = open(gpanim_filepath, "w", encoding="utf-8")
            f.write(json.dumps(gpanim, sort_keys=False, indent=2))
            f.close()
    
    print("Done!")

    return {'FINISHED'}


# ExportHelper is a helper class, defines filename and
# invoke() function which calls the file selector.
from bpy_extras.io_utils import ExportHelper
from bpy.props import StringProperty, BoolProperty, EnumProperty
from bpy.types import Operator


class ExportGPMESH(Operator, ExportHelper):
    """Export mesh in gpmesh format."""
    bl_idname = "export.gpmesh"  # important since its how bpy.ops.import_test.some_data is constructed
    bl_label = "Export as gpmesh"

    # ExportHelper mixin class uses this
    filename_ext = ".gpmesh"

    filter_glob: StringProperty(
        default="*.gpmesh",
        options={'HIDDEN'},
        maxlen=255,  # Max internal buffer length, longer would be clamped.
    )

    # List of operator properties, the attributes will be assigned
    # to the class instance from the operator settings before calling.
    export_gpmesh: BoolProperty(
        name="Export gpmesh",
        description="Writes the mesh as .gpmesh to disk",
        default=True
    )

    export_gpskel: BoolProperty(
        name="Export gpskel",
        description="Writes .gpskel file to disk",
        default=True
    )

    export_gpanim: BoolProperty(
        name="Export gpanim",
        description="Writes .gpanim file to disk",
        default=True
    )

    type: EnumProperty(
        name="Example Enum",
        description="Choose between two items",
        items=(
            ('OPT_A', "First Option", "Description one"),
            ('OPT_B', "Second Option", "Description two"),
        ),
        default='OPT_A',
    )

    def execute(self, context):
        return write_to_disk(context, self.filepath, self.export_gpmesh, self.export_gpskel, self.export_gpanim)


# Only needed if you want to add into a dynamic menu
def menu_func_export(self, context):
    self.layout.operator(ExportGPMESH.bl_idname, text="gpmesh")

# Register and add to the "file selector" menu (required to use F3 search "Text Export Operator" for quick access)
def register():
    bpy.utils.register_class(ExportGPMESH)
    bpy.types.TOPBAR_MT_file_export.append(menu_func_export)


def unregister():
    bpy.utils.unregister_class(ExportGPMESH)
    bpy.types.TOPBAR_MT_file_export.remove(menu_func_export)


if __name__ == "__main__":
    register()

    # test call
    bpy.ops.export.gpmesh('INVOKE_DEFAULT')
