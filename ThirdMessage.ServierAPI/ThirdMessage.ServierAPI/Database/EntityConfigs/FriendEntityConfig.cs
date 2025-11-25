using Microsoft.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore.Metadata.Builders;
using ThirdMessage.ServierAPI.Models;

namespace ThirdMessage.ServierAPI.Database.EntityConfigs;

public class FriendEntityConfig : IEntityTypeConfiguration<FriendModel>
{
    public void Configure(EntityTypeBuilder<FriendModel> builder)
    {
        builder.ToTable("Friends");
        builder.HasKey(f => f.FriendId);
        builder.Property(f => f.Uid).HasMaxLength(5).IsRequired();
        builder.Property(f => f.FriendId).HasMaxLength(5).IsRequired();
        builder.Property(f => f.UserName).HasMaxLength(50).IsRequired();

    }
}
