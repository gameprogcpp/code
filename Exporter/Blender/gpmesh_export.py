import bpy

def write_gpmesh(context, filepath, vertFormat):
    # Get current object
    obj = bpy.context.scene.objects.active
    if obj.type == 'MESH':
        mesh = obj.data
        f = open(filepath, 'w', encoding='utf-8')
        f.write("{\n")
        f.write("\t\"version\":1,\n")
        f.write("\t\"vertexformat\":\"" + vertFormat + "\",\n")
        f.write("\t\"shader\":\"BasicMesh\",\n")
        
        # For now, only one texture
        # figure out the file name...
        texname = filepath.split("\\")[-1].split("/")[-1].split(".")[0]
        # Make it a png
        texname += ".png"
        f.write("\t\"textures\":[\n")
        f.write("\t\t\"" + texname + "\"\n")
        f.write("\t],\n")
        
        # specular power
        f.write("\t\"specularPower\":100,\n")
         
        # vertices
        # We have to create our own storage for because uvs are stored separately
        verts = [dict() for x in range(len(mesh.vertices))]
        for v in mesh.vertices:
            verts[v.index]["pos"] = v.co
            verts[v.index]["norm"] = v.normal
        
        for l in mesh.loops:
            verts[l.vertex_index]["uv"] = mesh.uv_layers.active.data[l.index].uv
        
        f.write("\t\"vertices\":[\n")
        first = True
        for v in verts:
            if first:
                f.write("\t\t[")
                first = False
            else:
                f.write(",\n\t\t[")
            f.write("%f,%f,%f," % (v["pos"].x, v["pos"].y, v["pos"].z))
            f.write("%f,%f,%f," % (v["norm"].x, v["norm"].y, v["norm"].z))
            f.write("%f,%f" % (v["uv"].x, -1.0 * v["uv"].y))
            f.write("]")
        f.write("\n\t],\n")
        
        # indices
        f.write("\t\"indices\":[\n")
        first = True
        for p in mesh.polygons:
            if first:
                f.write("\t\t")
                first = False
            else:
                f.write(",\n\t\t")
            f.write("[%d,%d,%d]" % (p.vertices[0], p.vertices[1], p.vertices[2]))
        f.write("\n\t]\n")
        
        f.write("}\n")
        f.close()
    else:
        raise ValueError("No mesh selected")

    return {'FINISHED'}


# ExportHelper is a helper class, defines filename and
# invoke() function which calls the file selector.
from bpy_extras.io_utils import ExportHelper
from bpy.props import StringProperty, BoolProperty, EnumProperty
from bpy.types import Operator


class ExportGPMesh(Operator, ExportHelper):
    """Export to Game Programming in C++ mesh format"""
    bl_idname = "export_test.gpmesh"  # important since its how bpy.ops.import_test.some_data is constructed
    bl_label = "Export Mesh"

    # ExportHelper mixin class uses this
    filename_ext = ".gpmesh"

    filter_glob = StringProperty(
            default="*.gpmesh",
            options={'HIDDEN'},
            maxlen=255,  # Max internal buffer length, longer would be clamped.
            )
    
    vertFormat = EnumProperty(
            name="Vertex Format",
            description="Choose the vertex format",
            items=(('PosNormTex', "PosNormTex", "Position, normal, tex coord"),
                   ('PosTex', "PosTex", "Position, tex coord")),
            default='PosNormTex',
            )
    
    def execute(self, context):
        return write_gpmesh(context, self.filepath, self.vertFormat)


# Only needed if you want to add into a dynamic menu
def menu_func_export(self, context):
    self.layout.operator(ExportGPMesh.bl_idname, text="GPMesh Exporter (.gpmesh)")


def register():
    bpy.utils.register_class(ExportGPMesh)
    bpy.types.INFO_MT_file_export.append(menu_func_export)


def unregister():
    bpy.utils.unregister_class(ExportGPMesh)
    bpy.types.INFO_MT_file_export.remove(menu_func_export)


if __name__ == "__main__":
    register()

    # test call
    bpy.ops.export_test.gpmesh('INVOKE_DEFAULT')
